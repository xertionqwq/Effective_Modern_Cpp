#include<iostream>
#include<vector>
#include<string>

struct A{
    A(int param) { 
        // 编译器的实际操作
        // int a = 10;
        // float b = 20.f;
        // std::string c{"world"};

        // ==========================
        b = 50.f;
    }

    int a = 10; //就算打断点也执行不到这里
    float b = 20.f;
    std::string c{"world"};
};

struct B{
    B() { std::cout << "B()" << std::endl; }
    B(int data) :data(data) {
        std::cout << "B(int data)" << std::endl;
    }
    virtual void vfunc() { std::cout << "B::vfunc()" << std::endl; }

    int data;
};

struct C{
    // C中的构造函数里面安插了B的构造函数
    C(int data2) : data2(data2) { std::cout << "C(int data2)" << std::endl; }
    B b;
    int data2;
};

struct DB:public B{
    DB(int param) :data3(data3) {
        std::cout << "DB(int data3)" << std::endl;
    }
    int data3;
};

struct D{
    D(int param) : data4(param){}
    int data4;
};

struct E : public D{
    // D不存在默认构造，E要手动初始化
    E(int param, int d) : data5(param), D(d){}
    int data5;
};

struct F{
    F(int a) : data6(a){}
    F(int a,int b) : data6(a), data7(b){}
    F(int a,int b, int c) : data6(a), data7(b), data8(c){}
    F(int a,int b, int c, int d) : data6(a), data7(b), data8(c), data9(d){}
    void fun() { std::cout << "F::fun()" << std::endl; }

    int data6;
    int data7;
    int data8;
    int data9;
};

// 我想改写F的fun函数，但F已被大量使用，无法直接改写
// 所以选择继承，但继承又会出现G重复F的构造函数
struct G : public F{
    // 直接实例化F了
    using F::F;
    void fun() { std::cout << "G::fun()" << std::endl; }
};

int main() {
    // A a(1);
    // B b;
    // C c(5);
    DB bb(10);
    F f{5, 5};
    G g(5, 6);

    std::cout << "return done" << std::endl;
    return 0;
}