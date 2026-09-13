#include <iostream>
#include <vector>
#include <memory>

class Test{
public:
    Test() {
        std::cout << "Test() addr is: "<< this << std::endl;
    }
    Test(int a) : _a(a) {
        std::cout << "Test(int a) addr is: "<< this << std::endl;
    }

    void *operator new(size_t size) {
        std::cout << "operator new(size_t size)" << std::endl;
        return malloc(size);
    }

    void operator delete(void *ptr, size_t size) {
        std::cout << "operator delete(void *ptr, size_t size)" << std::endl;
        free(ptr);
    }

    ~Test() {
        std::cout << "~Test() addr is: "<< this << std::endl;
    }

private:
    int _a;
};

int main() {
    // int *p2 = (int *)malloc(sizeof(int) * 10);
    // free(++p2);// 崩溃, 不知道p2指向何处, 所以不知道释放多少的堆内存

    Test *p3 = new Test();
    delete p3;

    std::cout << "return done" << std::endl;
    return 0;
}