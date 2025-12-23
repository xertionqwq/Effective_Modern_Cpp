#include <iostream>
#include <string>
#include <vector>

class A
{
public:
    A(int param) : mm(param) {}

    A(A const &a) : mm(a.mm)
    {
        std::cout << "A (const A &a)" << std::endl;
    }

    A(A &&a) : mm(a.mm)
    {
        std::cout << "A (A &&a)" << std::endl;
        a.mm = 0;
    }

    A &operator=(const A &a)
    {
        std::cout << "A operator=(const A &a)" << std::endl;
        mm = a.mm;
        return *this;
    }

    A &operator=(A &&a)
    {
        std::cout << "A &operator=(A &&a)" << std::endl;
        mm = a.mm;
        a.mm = 0;
        return *this;
    }

    ~A()
    {
        std::cout << "~A()" << std::endl;
        delete nn;
    }

    void print() const
    {
        std::cout << "mm: " << mm << std::endl;
        std::cout << "nn: " << nn << std::endl;
    }

private:
    int mm;
    int *nn = nullptr;
};

int main()
{
    // A a{11};
    // A aa{91};
    // A b = a; // 无拷贝构造时，编译器自动合成
    // b = aa;  // 无拷贝复制时
    // b.print();

    A bb{69};
    A mm = std::move(bb); // 可在此处打断点，发现并没有实现移动，而是拷贝
    A nn = 91;
    nn = std::move(mm);

    std::cout << "return done" << std::endl;
    return 0;
}