#include <iostream>
#include <vector>
#include <string>
#include <array>

class Test{
public:
    Test(int a) : _ptr(new int(a)) {
        std::cout << "Test(int a) addr is: " << _ptr << std::endl;
    }
    Test(const Test& other) {
        // 重新分配内存，拷贝内容
        _ptr = new int(*(other._ptr));
        std::cout << "Test(copy) addr is: " << _ptr << std::endl;
    }
    ~Test() {
        std::cout << "~Test() addr is: " << _ptr << std::endl;
        delete _ptr;
    }
private:
    int *_ptr;
};

int main() {
    // for (int i = 0; i < 3; i++) {
    //     int *a = new int(10);
    //     // 内存间隔远
    //     std::cout << a << std::endl;
    // }

    // int *a = new int[3]{1, 22, 13};
    // 内存连续分配
    // std::cout << a << std::endl;
    // std::cout << a + 1 << std::endl;
    // std::cout << a + 2 << std::endl;
    // delete[] a;
    // delete a;
    
    Test *t = new Test[3] {Test(1), Test(2), Test(3)};
    delete [] t;

    std::cout << "return done" << std::endl;
    return 0;
}