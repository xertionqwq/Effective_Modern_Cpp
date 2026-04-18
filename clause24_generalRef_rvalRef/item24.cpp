#include <iostream>
#include <vector>
#include <alloca.h>

// 模板通用引用, T&& + 类型推导
template<class T>
void func(T &&param) {
    std::cout << "T(&&)" << std::endl;
}

// 右值引用, T&& + 显式指定类型
template<class T>
void func(std::vector<T> &&param) {
    std::cout << "std::vector<T>(&&)" << std::endl;
}

// 右值引用
template<class T>
void func(const T &&param) {
    std::cout << "const T(&&)" << std::endl;
}

template<class T>
class vector {
public:
    void push_back(T &&x);
};

// 可变参数模板的通用引用, Args&&... + 类型推导
template<class T>
class arr{
public:
    template <class... Args>
    void emplace_back(Args &&...args);
};

int main()
{
    int a = 0;
    func(a);
    func(10);
    func<int>(10); // 指定类型, 只能传右值
    // func<int>(a); // 报错

    // 基于lambda表达式的auto通用引用
    auto timeFuncInvoation = [](auto &&func, auto &&...params) {
        struct timespec start, end;
        std::forward<decltype(func)>(func)(
            std::forward<decltype(params)>(params)...);
        clock_gettime(CLOCK_MONOTONIC, &end);
        return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    };

    std::cout << "return done" << std::endl;
    return 0;
}