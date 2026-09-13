#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class A
{
public:
    A(std::string str)
    {
        std::cout << "A(std::string str)" << std::endl;
        _data = str;
    }
    A(const A &aa)
    {
        std::cout << "A (const A &aa)" << std::endl;
        _data = aa._data;
    }
    A(A &&aa) noexcept
    {
        std::cout << "A (A &&aa)" << std::endl;
        _data = aa._data;
        aa._data = "";
    }

private:
    std::string _data;
};

// swap函数是否抛出异常是灵活的
template <class T, size_t N>
void swap(T (&a)[N], T (&b)[N]) noexcept(noexcept(swap(*a, *b)));
                                // 是否抛出异常取决于交换数组元素是否抛出异常

int main()
{
    std::vector<A> vec;
    vec.reserve(2);
    vec.push_back(A("blue"));
    vec.push_back(A("blue"));
    vec.push_back(A("blue")); // 该段会构建新的vec并复制此前的数据
                              // 若给出noexcept, 则会变成移动数据
    vec.push_back(A("blue"));

    int a = 91;
    int b = 69;
    std::swap(a, b);

    std::cout << "return done" << std::endl;
    return 0;
}