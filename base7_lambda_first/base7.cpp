#include<iostream>
#include<string>
#include<vector>
#include<memory>

int globle_a = 10;
class SizeCmpr
{
public:
    SizeCmpr(size_t n) : sz(n) {}
    bool operator()(const std::string &s){
        return s.size() > sz;
    }

private:
    size_t sz;
};
class A{
public:
    void print() { std::cout << "class A" << std::endl; }
    void test()
    {
        auto foo = [this]
        {
            print();
            x = 5;
        };
    }

private:
    int x;
};

int main() {
    std::string str = "hello,world";
    size_t sz = 999, ss = 789;
    auto res = [=](const std::string &a)
    {
        return a.size() > sz;//使用什么变量才会捕获什么变量
    };
    auto size = sizeof(res);
    SizeCmpr sizecmpr(sz);
    std::cout << res(str) << std::endl;
    std::cout << sizecmpr(str) << std::endl;

    auto change = [sz]() mutable
    {
        sz = 10;
    };

    auto test = [sz]() -> auto
    {
        size_t t = 110;
        return t > sz;
    };

    auto foo = [](auto a)
    {
        return a;
    };
    int three = foo(3);
    std::cout << three << std::endl;

    int b = 69;
    static int c = 91;
    auto func1 = [b]//全局或静态变量无需捕获，可直接使用
    {
        std::cout << "b is: " << b << std::endl;
        globle_a = 911;
        c = 49;
    };
    func1();

    auto func2 = [sz]
    {
        std::cout << "sz is:" << sz << std::endl;
    };
    sz = 666;//修改sz仍然不会改变func2的捕获
    func2();
    auto func3 = [](int i) {
        if (i > 0) {
            return i;
        } else {
            return -i;
        }
    };
    auto func4 = [b1 = b, size = sz]()
    {
        std::cout << "func4 has captured b and sz" << std::endl;
    };

    auto cnt_copied = std::make_unique<int>(1314);
    // auto copy = cnt_copied;
    // int v1 = 0;
    // int v2 = 0;
    //对于无法复制的对象可进行移动操作，并且接收右值
    auto add = [v1 = 1, v2 = std::move(cnt_copied)](int x, int y)
    {
        return v1 + (*v2) + x + y;
    };

    std::cout
        << "return done" << std::endl;
    return 0;
}