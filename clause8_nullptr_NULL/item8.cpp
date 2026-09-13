#include<iostream>
#include<string>
#include <memory>

void f(int a) {
    std::cout << "f(int)" << std::endl;
}
void f(void* a) {
    std::cout << "f(void*)" << std::endl;
}
void f(bool a) {
    std::cout << "f(bool)" << std::endl;
}
// void f(long a) {
//     std::cout << "f(long)" << std::endl;
// }

int f1(std::shared_ptr<int> sep) {
    return 5;
}
int f2(std::unique_ptr<int> sep) {
    return 9;
}
int f3(int *sep) {
    return 12;
}

template<typename FunType, typename PtrType>
decltype(auto) func(FunType f, PtrType ptr) {
    return f(ptr);
}

int main() {
    int *p1 = 0;    //可使用0直接初始化指针
    int *p2 = NULL;
    int *p3 = nullptr;

    auto a = 0;         //int
    // auto b = NULL;      //long
    auto c = nullptr;   //std::nullptr_t
    f(0);
    // f(NULL);            //只有存在long重载时在可以确定
    f(nullptr);

    int mmm = 0;
    // int *pm = mmm;//变量0无法转为int*

    auto res1 = func(f3, nullptr); //唯一正确
    // auto res2 = func(f3, 0);    //传入0时,PtrType推导为int
                                //而int无法转为int*
    // auto res3 = func(f1, NULL); //传入NULL时，PtrType推导为long int

    std::cout << "return done" << std::endl;
    return 0;
}