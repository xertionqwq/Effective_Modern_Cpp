#include <iostream>
#include <memory>
#include <unordered_map>

class Widget{
public:
    Widget(int id) : id_(id) {
        std::cout << "Widget " << id_ << " created." << std::endl;
    }
    ~Widget() {
        std::cout << "Widget " << id_ << " destroyed." << std::endl;
    }   
private:
    int id_{-1};
};

// 假设widget类加载需要大量资源
std::unique_ptr<const Widget> loadWidget(int id) {
    // 耗时操作
    std::unique_ptr<const Widget> wptr(new Widget(id));
    std::cout << "loadWidget func id: " << id << std::endl;
    return wptr;
}

std::shared_ptr<const Widget> fastLoadWidget(int id) {
    // 维护静态变量-缓存
    static std::unordered_map<int, std::weak_ptr<const Widget>> cache;
    // 升级为临时shared指针, 验证对象是否存活
    auto object = cache[id].lock();
    if (!object) {
        // 没有, 则分配内存, 放入缓存
        object = loadWidget(id);
        cache[id] = object;
    } else {
        std::cout << "fastLoadWidget func id: " << id << std::endl;
    }
    return object;
}

class B;
class A{
public:
    A() {std::cout << "A()" << std::endl;}
    ~A() {std::cout << "~A()" << std::endl;}

    std::shared_ptr<B> bptr;
};
class C{
public:
    C() {std::cout << "C()" << std::endl;}
    ~C() {std::cout << "~C()" << std::endl;}

    std::shared_ptr<B> bptr;
};
class B{
public:
    B() {std::cout << "B()" << std::endl;}
    ~B() {std::cout << "~B()" << std::endl;}

    std::shared_ptr<A> aptr;
};

int main() {
    // 4. 经典使用, 查看对象生命状态
    // {
    //     auto sptr = std::make_shared<int>(42);
    //     std::weak_ptr<int> wptr(sptr);  // 依赖于 shared_ptr 的生命周期
    //     std::weak_ptr<int> wptr2 = sptr;  // 直接从 shared_ptr 初始化 weak_ptr
    //     sptr = nullptr;
    //     if (wptr.expired()) {
    //         std::cout << "sptr 已重置为 nullptr" << std::endl;
    //     }
    // }

    // if (wptr.expired()) {
    //     std::cout << "wptr 已过期" << std::endl;
    // } else {
    //     std::cout << "wptr 仍然有效，值为: " << *wptr.lock() << std::endl;
    // }

    // if (wptr.lock()) {
    //     std::cout << "wptr2 仍然有效，值为: " << *wptr2.lock() << std::endl;
    // } else {
    //     std::cout << "wptr2 已过期" << std::endl;
    // }

    // 核心: shared掌管对象死活, weak只是观察者, 不会影响对象生命周期
    // {
    //     auto widgetPtr = fastLoadWidget(0);
    //     widgetPtr = fastLoadWidget(1); // 此时 0 无人持有, 立即销毁对象
    //     std::cout << "----------------" << '\n';

    //     auto widgetPtr1 = fastLoadWidget(1); // 1 强引用计数+1, 此时为引用数为2
    //     widgetPtr1 = fastLoadWidget(3); // 1 强引用计数-1, 3 强引用计数+1, 此时为引用数为1
    // }   // 离开作用域, 1 3 均无引用计数, 对象全部销毁

    {
        auto b = std::make_shared<B>();
        auto a = std::make_shared<A>();
        auto c = std::make_shared<C>();
        a->bptr = b;
        c->bptr = b;
        b->aptr = a;
    } // 循环引用, c 正常释放, 而 a b 无法销毁, 造成内存泄露

    std::cout << "return done" << std::endl;
    return 0;
}