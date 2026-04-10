#include <iostream>
#include <memory>
#include <vector>

class Widget;
class Widget{
public:
    Widget() {
        std::cout << "Widget created." << std::endl;
    }
    Widget(int id) : id_(id) {
        std::cout << "Widget " << id_ << " created." << std::endl;
    }
    ~Widget() {
        std::cout << "Widget " << id_ << " destroyed." << std::endl;
    }   
private:
    int id_{-1};
};

int computePriority() {
    throw std::runtime_error("computePriority failed");
    return 55;
}

void processWidget(std::shared_ptr<Widget> wptr, int priority) {
    std::cout << "processWidget done" << std::endl;
}

class Airplane
{
private:
    struct AirplaneRep
    {
        unsigned long miles{10}; // 8
        char type{'A'};          // 1
    };
    // 底层经典布局, 嵌入式指针
    union
    {
        AirplaneRep rep{}; // 16
        Airplane *next;  // 8
    }; // 16
public:
    Airplane() = default;
    unsigned long getMiles() const { return rep.miles; }
    char getType() const { return rep.type; }
    void set(unsigned long miles, char type)
    {
        rep.miles = miles;
        rep.type = type;
    }

    // 重复malloc会有性能损失, 所以需要单次申请指定内存大小
    // 重载new和delete
    static void *operator new(size_t size);
    static void operator delete(void *ptr);

    ~Airplane() { std::cout << "Airplane::~Airplane() called" << std::endl; }

private:
    static const int BLOCK_SIZE;
    static Airplane *headOfFreelist;
};

Airplane *Airplane::headOfFreelist = nullptr;
const int Airplane::BLOCK_SIZE = 512;

void *Airplane::operator new(size_t size)
{
    Airplane *p = headOfFreelist;
    if (p) {
        headOfFreelist = p->next;
        return p;
    } else {
        // ::operator new是全局的new, 直接调用全局的new来分配内存, 不会调用Airplane的new
        Airplane *newBlock = static_cast<Airplane *>(::operator new(BLOCK_SIZE * sizeof(Airplane)));
        for (int i = 1; i < BLOCK_SIZE - 1; ++i) {
            newBlock[i].next = &newBlock[i + 1];
        }
        newBlock[BLOCK_SIZE - 1].next = nullptr;
        p = newBlock;
        headOfFreelist = &newBlock[1];
    }
    return p;
}

void Airplane::operator delete(void *ptr)
{
    if (ptr == nullptr)
        return;

    Airplane *deleteMe = static_cast<Airplane *>(ptr);
    deleteMe->next = headOfFreelist;
    headOfFreelist = deleteMe;
}
int main() {
    // 优先级函数提前抛出异常, 对象被构造了, 但是没有析构, 造成内存泄漏
    // processWidget(std::shared_ptr<Widget>(new Widget), computePriority());

    // 使用make_shared, 只有一个内存分配, 先构造对象, 然后调用函数, 如果函数抛出异常, 对象会被正确析构
    // processWidget(std::make_shared<Widget>(), computePriority());

    // 或者提前构造对象, 然后调用函数, 如果函数抛出异常, 对象会被正确析构
    auto upw(std::make_unique<Widget>());
    processWidget(std::move(upw), computePriority());

    // auto spv = std::make_shared<std::vector<int>>({1, 2, 3}); // 报错, {}无法进行完美转发
    auto upv = std::make_unique<std::vector<int>>(std::initializer_list<int>{1, 2, 3});

    // auto aspv = std::make_shared<Airplane>(); // 没有执行new/delete的重载
    // auto aspv_ = std::make_shared<Airplane>(new Airplane()); // 执行了new/delete的重载, 但是内存泄漏了
    std::unique_ptr<Airplane> _aspv(new Airplane()); // 执行了new/delete的重载, 但是内存泄漏了

    auto pBigType = std::make_shared<Airplane>();
    std::weak_ptr<Airplane> pBigTypeWeak(pBigType);
    pBigType.reset();  // 强引用计数减为0, 对象被析构, 但是内存没有回收, weak仍在观察
    std::cout << "over" << std::endl;

    std::cout << "return done" << std::endl;
    return 0;
}