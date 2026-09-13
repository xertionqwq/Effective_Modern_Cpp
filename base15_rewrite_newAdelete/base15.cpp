#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Airplane
{
private:
    struct AirplaneRep
    {
        unsigned long miles{10}; // 8
        char type{'A'};          // 1
    };
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

int main()
{
    // 不重写, p3, p4, p5分配的地址并不连续
    // new包含两步: 1. 在堆上分配内存 2. 调用构造函数并将地址传给p3, p4, p5
    Airplane *p3 = new Airplane();
    std::cout << p3 << std::endl;
    
    Airplane *p4 = new Airplane();
    std::cout << p4 << std::endl;

    Airplane *p5 = new Airplane();
    std::cout << p5 << std::endl;

    delete p3;
    delete p4;
    delete p5;

    std::cout << "return done" << std::endl;
    return 0;
}

