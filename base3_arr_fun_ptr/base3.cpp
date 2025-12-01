#include<iostream>
#include<vector>
#include<string>

// 使用类型别名
// typedef bool funx(int, int);
// typedef bool (*funpp)(int, int);
using fun3x = bool(int, int);
using fun3p = bool (*)(int, int);
using Myint = int;

template <class T>
using MyVec = std::vector<T>;

void fun(int a[10]) {}
// void fun(int a[]) {};
// void fun(int *a) {};
void fun10(int (*a)[10]) {}
void fun2(int (*a)[2]) {}
void fun3(int m) {
    std::cout << "fun3 has done nothing" << std::endl;
}

bool fun1(int a, int b) {
    return a == b;
}
// 函数指针的声明，无法直接定义
// bool (*funp)(int a, int b) {
//     return a == b;
// }
bool (*funp)(int a, int b) = &fun1;
bool (&funref1)(int, int) = fun1;

void funOf(int m, bool (*funp)(int, int)) {};
void funOf2(int n, fun3p func) {};//两种方式等价，只不过声明了函数数据类型

bool (*fun3(double a))(int, int);
fun3x *fun3(int m, int n);//两个的*均不可以省略
fun3p fun3(char c);


int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    int *pa = arr;
    // for (int i = 0; i < 5; i++) {
    //     std::cout << *p << std::endl;
    //     p++;
    // }

    //数组指针
    int (*arrp)[5] = &arr;
    // for (int i = 0; i < 5; i++) {
    //     std::cout << arrp[i] << std::endl;
    //     std::cout << (*arrp[i]) << std::endl;
    //     std::cout << (*arrp)[i] << std::endl;
    // }

    Myint a = 91, b = 69;
    //指针数组
    int *parr[5] = {&a, &b};
    // for (int i = 0; i < 2; i++) {
    //     std::cout << parr[i] << std::endl;
    //     std::cout << *parr[i] << std::endl;
    // }

    //数组引用
    int(&arrref)[5] = arr;
    // std::cout << arrref[0] << std::endl;
    // int &refarr[5];

    // &"hello world";
    // const char *p = "hello world";
    // const char (*p)[12] = "hello world";
    // const char (&p2)[12] = "hello world";
    // char str[12] = "hello world";
    
    //fun10(arr);
    //funp = &fun1;
    bool c = fun1(1, 2);//函数指针使用
    bool d = (*fun1)(2, 2);
    std::cout << c << ' ' << d << std::endl;
    bool e = (*funp)(9, 1);
    std::cout << e << std::endl;
    MyVec<Myint> vec;

    std::cout << "return done" << std::endl;
    return 0;
}

