#include <iostream>
#include <string>

namespace cpp98
{
    struct B;

    // c++98使用私有成员实现禁用效果
    struct A
    {
    public:
        A(int data) : data_(data) {}

    private:
        friend class B;
        A(const A &a);            // 禁止拷贝构造, 且不给出定义
        A &operator=(const A &a); // 禁止赋值拷贝
        int data_;
    };

    struct B
    {
    public:
        B()
        {
            A a(10);
            // A a_(A(61)); // 编译不会报错, 在链接阶段崩溃(找不到定义)
            // undefined reference to `A::A(A const&)
            // 错误不明显
        }
    };

    // c++98无法实现
    class test
    {
    public:
        template <typename T>
        void funcPtr(T *ptr) {}

    private:
        // template<> // 报错
        void funcPtr(void *ptr);
    };
}

struct B;
struct A
{
public:
    A(int data) : data_(data) {}
    A(const A &a) = delete; // 直接显示禁止, 意图更加明显
    A &operator=(const A &a) = delete;

private:
    friend class B;
    int data_;
};
struct B
{
public:
    B()
    {
        A a(10);
        // A a_(A(61)); // use of deleted function ‘A::A(const A&)’
    }
};

bool isLucky(int num)
{
    return num == 9;
}
bool isLucky(char) = delete; // 控制传参类型

// 禁用模板实例化
template <typename T>
void funcPtr(T *ptr) {}
template <>
void funcPtr(void *ptr) = delete;

int main()
{
    // cpp98::A a = 91; // 这是拷贝构造,无法使用,详情见clause7
    cpp98::A a(91);
    // A aa = a;
    cpp98::A a_(69);
    // a_ = a;
    cpp98::B b;

    B b_;

    int res{isLucky(9)};
    // int res_{isLucky('a')};

    funcPtr(new int{11});
    void *ptr{nullptr};
    // funcPtr(ptr);

    std::cout << "return done" << std::endl;
    return 0;
}