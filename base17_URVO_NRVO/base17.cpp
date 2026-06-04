#include <iostream>
#include <new>
#include <memory>

class Test{
public:
    Test() {
        std::cout << "Test()" << std::endl;
    }
    Test(int a) : a(a) {
        std::cout << "Test(int a)" << std::endl;
    }

    ~Test() = default;

    Test(const Test& other) : a(other.a) {
        std::cout << "Test copy" << std::endl;
    }

    Test(Test&& other) : a(other.a) {
        std::cout << "Test move" << std::endl;
    }

private:
    int a = 0;
};

Test getTest1() {
    return Test(1);
}

Test getTest2() {
    Test t(2);
    return t;
}

Test getTest3() {
    Test t(3);
    return t;
}

// 1.编译器优化URVO（Unnamed Return Value Optimization）   
void getTest1(Test& _t) {
    new (&_t) Test(1);
}
// 针对有具名对象再次进行URVO优化
void getTest2(Test& _t) {
    Test t(2);
    new (&_t) Test(std::move(t));
}
// NRVO（Named Return Value Optimization）, 在URVO基础上，编译器会优化掉具名对象的复制或移动
void getTest3(Test& _t) {
    new (&_t) Test(3);
}

int main() {
    // Test t1 = getTest1();
    // Test t2 = getTest2(); // c++17强制打开URVO, 但是NRVO却可以被关闭
                          // 所以在c++17中, 关闭优化, 只出现一次移动/拷贝
    // Test t3 = getTest3();

    // 编译器针对URVO的实际优化
    // char buffer[sizeof(Test)];
    // Test *ptr = reinterpret_cast<Test*>(buffer);
    // getTest1(*ptr); // 关闭返回值优化, 运行结果和开启返回值优化一致

    char buffer[sizeof(Test)];
    Test *ptr = reinterpret_cast<Test*>(buffer);
    getTest2(*ptr);

    std::cout << "-----------------" << std::endl;

    std::cout << "return done" << std::endl;
    return 0;
}