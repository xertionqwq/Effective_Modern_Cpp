#include<stdexcept>
#include<iostream>
#include<typeinfo>
#include <cstdint>

class A{
public:
    A() = default;

    void funA() {
        std::cout << "A::funA()" << std::endl;
    }
    // void fun2() {
    //     std::cout << "A::fun2()" << std::endl;
    // }

private:
    int data1_;
};

class CA:public A{
public:
    CA(){
        data2_ = 91;
    }

    void funCA() {
        std::cout << "data2_ is: " << data2_ << std::endl;
        std::cout << "CA::funCA()" << std::endl;
    }

private:
    int data2_;
};

struct Base {
    virtual void fun() {
        std::cout << "Base::fun()" << std::endl;
    }
};
struct Derived : public Base{
    virtual void fun() override {
        std::cout << "Derived::fun()" << std::endl;
    }
};

class MyArr{
private:
    int data[5] = {1, 2, 3, 4, 5};
    int size = 5;

public:
    //1.const版本，返回const引用，无法修改元素
    const int& operator[](int idx) const {
        if (idx < 0 || idx >= size) {
            throw std::out_of_range("Index out of bound");
        }
        return data[idx];
    }
    //2.非const版本，返回const引用，可以修改元素
    int& operator[](int idx) {
        const MyArr *cthis = static_cast<const MyArr *>(this);//将this指针转为const版本
        int &res = const_cast<int &>(cthis->operator[](idx));//调用const版，并且去掉const，避免代码重复
        return res;
    }
};

int main() {
    // static_cast 1.
    float f = 61.f;
    int i = static_cast<int>(f);
    int ii = f;//发生隐式转换，不安全

    // static_cast 2.
    A aa;
    void *vdp = static_cast<void *>(&aa);
    int *ip = static_cast<int *>(vdp);
    std::cout << "*ip: " << *ip << std::endl;

    // static_cast 3.
    CA ca;
    A a_ = static_cast<A>(ca);      //上行可以
    // a_.funA();
    // CA aca = static_cast<CA>(a_); //下行报错

    // static_cast 4.
    Derived de;
    Base ba;
    Base base = static_cast<Base>(de);//允许上行，但是多态消失
    // base.fun();
    // Derived de_ = static_cast<Derived>(ba);//下行报错

    // static_cast 5.
    // CA *pca = static_cast<CA *>(&a);
    // pca->funCA();               //下行不安全,data2_并未初始化
    // CA &refca = static_cast<CA &>(a);
    // refca.funCA();              //下行不安全,每次运行data2_的结果都是随机的
    //                             //但是不报错

    // static_cast 6.
    // Base *pb = static_cast<Base *>(&de);
    // pb->fun();
    // Derived *pde = static_cast<Derived *>(&ba);//下行不安全
    // pde->fun();//Derived isn't initialed, so fun for Base
    // Derived *safepde = static_cast<Derived *>(pb);//子类已初始化，上行再下行，安全
    // safepde->fun();

    // dynamic_cast
    Base *pb_dy = dynamic_cast<Base *>(&de);//上行安全
    pb_dy->fun();
    Derived *pde_dy = dynamic_cast<Derived *>(&ba);//下行不安全，返回空指针
    if (pde_dy) {
        pde_dy->fun();
    }
    Derived *safepde = static_cast<Derived *>(pb_dy);//子类已初始化，上行再下行，安全
    safepde->fun();

    // const_cast
    const char *str = "hello world";
    char *p = const_cast<char *>(str);
    // p[1] = 'm';//编译可以通过，但是出现段错误
    MyArr arr;
    const MyArr carr;
    arr[1] = 91;
    std::cout << "arr[1] = " << arr[1] << std::endl;
    std::cout << "carr[1] = " << carr[1] << std::endl;
    // carr[1] = 69; //编译报错
    
    // reinterpret_cast
    // 强制转换，极度不安全
    // 1. 普通指针转不相关指针
    int a = 0x12345678;
    int* pa = &a;
    double* pd = reinterpret_cast<double*>(pa); // 直接将int*的二进制解释为double*
    // 2. 指针转整数（需确保整数足够存储指针，如64位系统用uint64_t）
    uint64_t ptr_val = reinterpret_cast<uint64_t>(pa);
    // 整数转回指针
    int* pa2 = reinterpret_cast<int*>(ptr_val);
    // 不安全行为
    // int aaa = 10;
    // double* pd = reinterpret_cast<double*>(&a);
    // // 未定义行为！int和double的二进制格式完全不同
    // std::cout << *pd << std::endl;

    std::cout
        << "return done" << std::endl;
    return 0;
}