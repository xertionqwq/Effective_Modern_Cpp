#include <iostream>
#include <vector>
#include <string>

// 使用类型别名
// typedef bool funx(int, int);
// typedef bool (*funpp)(int, int);
using fun3x = bool(int, int);
using fun3p = bool (*)(int, int);
using Myint = int;

template <class T>
using MyVec = std::vector<T>;

// 函数的三种等价声明方式
void fun(int a[10]) {}
// void fun(int a[]) {};
// void fun(int *a) {};

// 参数是数组指针,并且大小已经指定
void fun10(int (*a)[10]) {}
void fun5(int (*a)[5]) {}

void fun3(int m)
{
    std::cout << "fun3 has done nothing" << std::endl;
}

bool fun1(int a, int b)
{
    return a == b;
}
// 函数指针的声明，无法直接定义
// bool (*funp)(int a, int b) {
//     return a == b;
// }
bool (*funp)(int a, int b) = &fun1;
bool (&funref1)(int, int) = fun1;

// 函数指针作为参数传递
void funOf(int m, bool (*funp)(int, int)) {};
void funOf2(int n, fun3p func) {}; // 两种方式等价，只不过声明了函数数据类型

// 函数指针作为返回值
bool (*fun3(double a))(int, int);
fun3x *fun3(int m, int n); // 两个的*均不可以省略
fun3p fun3(char c);

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    // 数组退化为指针
    int *pa = arr;
    // for (int i = 0; i < 5; i++) {
    //     std::cout << *pa << " ";
    //     pa++;
    // }
    // std::cout << std::endl;

    // 数组指针
    int (*arrp)[5] = &arr;
    // for (int i = 0; i < 5; i++) {
    //     std::cout << arrp[i] << std::endl;
    //     // std::cout << (*arrp[i]) << std::endl;// 错误访问
    //     std::cout << (*arrp)[i] << std::endl;// 先解引用得到数组,再访问数组元素
    // }

    Myint a = 91, b = 69;
    // 指针数组
    int *parr[5] = {&a, &b};
    // for (int i = 0; i < 2; i++) {
    //     std::cout << parr[i] << std::endl;
    //     std::cout << *parr[i] << std::endl;
    // }

    // 数组引用
    int (&arrref)[5] = arr;
    // std::cout << arrref[0] << std::endl;
    // int &refarr[5]; //有指针数组,但不存在引用数组,因为引用必须初始化且不能更改引用目标

    &"hello world"; // 字符串字面值是常量数组(const char [12]),是左值
    // char *ppp = "hello world"; // 允许但不推荐,兼容C风格,字符串字面值是常量,不能通过该指针修改内容
    // const char *p = "hello world";
    // const char (*p)[12] = &"hello world";
    // std::cout << (*p)[0] << std::endl;
    // const char (&p2)[12] = "hello world";
    // char str[12] = "hello world";

    // fun10(arrp);
    fun5(arrp);
    fun5(static_cast<int (*)[5]>(&arr));

    // funp = &fun1;
    bool c = fun1(1, 2); // 函数指针使用
    bool d = (*fun1)(2, 2);
    std::cout << c << ' ' << d << std::endl;
    bool e = (*funp)(9, 1);
    std::cout << e << std::endl;
    MyVec<Myint> vec;

    std::cout << "return done" << std::endl;
    return 0;
}
