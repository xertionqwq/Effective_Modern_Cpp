#include<iostream>
#include<cstdint>
#include<vector>
#include<typeinfo>

using Fun = void();

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
        // std::cout << "A::~A()" << std::endl;
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
    // virtual void vAfun2() { std::cout << "B::vBfun2()" << std::endl; }

    void fun1() { std::cout << "B::fun1()" << std::endl; }
    void fun2() { std::cout << "B::fun2()" << std::endl; }

    virtual ~B() {
        // std::cout << "B::~B()" << std::endl;
        delete data3_;
    }

private:
    int *data3_;
};

template<typename T>
decltype(auto) getVptr(T param) {
    return (void **)*(void **)&param;
}
template<typename T>
decltype(auto) getVptr(T *param) {
    return (void **)*(void **)param;
}

template<typename T, typename idx>
decltype(auto) getVfunc(T &param, idx i) {
    if (i < 1)
        return nullptr;
    auto ptr = getVptr(param);
    return (Fun *)*(ptr + i - 1);
}

template<typename T>
decltype(auto) getVinfo(T &param) {
    return (std::type_info*)*((std::int64_t *)*(std::int64_t *)(&param) - 1);
    // auto x = (std::int64_t *)&param - 1;
    // return (std::type_info *)*((std::int64_t *)*x);
}

void test(A *a) {
    if (typeid(*a) == typeid(A)) {
        A *pa = static_cast<A *>(a);
        pa->fun1();
    } else if (typeid(*a) == typeid(B)) {
        B *pb = static_cast<B *>(a);
        pb->fun2();
    }
}

int main () {
    B b;
    A a;
    A *pba = static_cast<A *>(&b);
    A aa = static_cast<A>(b);
    // pba->vAfun1(); //使用指针即为多态，可调用子类重写的虚函数
    // aa.vAfun1();
    // a.vAfun1();

    // std::cout << "aa:" << getVptr(aa) << std::endl;
    // aa.vAfun1();
    // aa.fun1();
    // aa.fun2();
    // std::cout << "======================" << std::endl;

    // std::cout << "pba:" << getVptr(pba) << std::endl;
    // pba->vAfun1();
    // pba->fun1();
    // pba->fun2();

    B bb;
    Fun *pfun = nullptr;
    // std::cout << "虚函数表地址，即虚表指针：" << (void **)*(void **)&bb << std::endl;
    // std::cout << "第一个虚函数地址：" << (std::int64_t *)(*(std::int64_t *)*((std::int64_t *)&b)) << std::endl;
    // pfun = (Fun *)(*(std::int64_t *)*((std::int64_t *)&b));
    // pfun();

    // std::type_info *base_type = getVinfo(b);
    // std::cout << "the typeinfo is: " << base_type->name() << std::endl;
    // std::cout << "typeid(Base).name:" << typeid(B).name() << std::endl;

    // A *base = &b;
    // test(base);
    // test(&b);

    A *nn = dynamic_cast<A *>(&b);
    // B *mm = dynamic_cast<B *>(&a);
    B *mmm = dynamic_cast<B *>(nn);

    std::cout << "return done" << std::endl;
    return 0;
}
