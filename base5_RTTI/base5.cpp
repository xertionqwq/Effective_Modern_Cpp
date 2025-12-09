#include<iostream>
#include<string>
#include<vector>
#include<typeinfo>

class A {
public:
    A() {
        data1_ = new int();
        data2_ = new int();
    }

    virtual void vAfun1() { std::cout << "A::vAfun1()" << std::endl; }
    virtual void vAfun2() { std::cout << "A::vAfun2()" << std::endl; }

    void fun1() { std::cout << "A::fun1()" << std::endl; }
    void fun2() { std::cout << "A::fun2()" << std::endl; }

    virtual ~A() {
        std::cout << "A::~A()" << std::endl;
        delete data1_;
        delete data2_;
    }

private:
    int *data1_;
    int *data2_;
};

class B :public A{
public:
    B() {
        // std::cout << "B::B()" << std::endl;
        data3_ = new int();
    }

    virtual void vAfun1() override { std::cout << "B::vAfun1()" << std::endl; }
    virtual void vBfun1() { std::cout << "B::vBfun1()" << std::endl; }
    virtual void vAfun2() { std::cout << "B::vBfun2()" << std::endl; }

    void fun1() { std::cout << "B::fun1()" << std::endl; }
    void fun2() { std::cout << "B::fun2()" << std::endl; }

    virtual ~B() {
        std::cout << "B::~B()" << std::endl;
        delete data3_;
    }

private:
    int *data3_;
};

using Fun = void();

int main () {
    A a;
    // a.vAfun1();

    B bb;
    Fun *pfun = nullptr;
    std::cout << "虚函数表地址，即虚表指针：" << (void **)*(void **)&bb << std::endl;

    std::cout << "return done" << std::endl;
    return 0;
}