#include<iostream>
#include<cstdint>
#include<string>
#include<vector>

struct test1 {
    int a;  //4
    short b;//2+2
    int c;  //4
    short d;//2+2
};//sum16

struct test2 {
    int a;  //4
    int c;  //4
    short b;//2
    short d;//2
};//sum12

struct test3 {
    int a;
    short b;
};//sum8

struct test4 : public test3 {
    short c;
};//sum12

class A {
public:
    virtual void vAfun1() {
        std::cout << "A::vAfun1()" << std::endl;
    }
    virtual void vAfun2() {
        std::cout << "A::vAfun2()" << std::endl;
    }
    void Afun1() {
        std::cout << "A::Afun1()" << std::endl;
    }
    void Afun2() {
        std::cout << "A::Afun2()" << std::endl;
    }
private:
    int date1_;
    int data2_;
};

class B:public A{
public:
    virtual void vBfun1() {
        std::cout << "B::vBfun1()" << std::endl;
    }
    virtual void vBfun2() {
        std::cout << "B::vBfun2()" << std::endl;
    }

    virtual void vAfun1() override {
        std::cout << "B::vAfun1()" << std::endl;
    }
    void Bfun2() {
        std::cout << "B::Bfun2()" << std::endl;
    }

private:
    int data3_;
};

using Fun = void();

int main()
{
    auto size1 = sizeof(test2);
    auto size2 = sizeof(test4);
    // std::cout << size1 << std::endl;
    // std::cout << size2 << std::endl;

    A a;
    Fun *pfun = nullptr;
    auto vptr = (std::int64_t*)(&a);
    auto vtable = (std::int64_t *)*vptr;
    auto virfun1 = (Fun *)*vtable;
    auto virfun2 = (Fun *)*(vtable + 1);//通过指针移动得到虚函数地址
    // virfun1();
    // virfun2();

    B b;
    void **vptr1 = (void **)&b;
    void **vtable1 = (void **)*vptr1;
    std::cout << "虚函数表地址，即虚表指针：" << vptr1 << std::endl;
    std::cout << "虚函数表的第1个虚函数的地址：" << vtable1 << std::endl;
    Fun *pfun1 = (Fun *)*(vtable1);
    std::cout << "虚函数1运行：";
    pfun1();
    std::cout << "虚函数表的第2个虚函数的地址：" << vtable1 + 1 << std::endl;

    std::cout << "return done" << std::endl;
    return 0;
}