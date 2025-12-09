#include<iostream>
#include<type_traits>
#include<vector>

bool fun1(int a, int b) {
    std::cout << "fun1 has worked" << std::endl;
    return a == b;
}
bool (*fun1p)(int a, int b) = &fun1;

void fun2(int x, bool(*fun1p)(int,int)){
    std::cout << "fun2 has worked " << fun1p(10,20) << std::endl;
}

template<typename Container, typename Index>
auto getVal(Container& c, Index i) //写法可以使用，但仍需改进
    -> decltype(c[i]) {         //c++11写法，尾置返回值类型
    return c[i];
}

template<typename Container, typename Index, typename Value>
Value &getVal_error(Container& c, Index i) {
    return c[i];
}

template<typename Container, typename Index>
auto getElem_error(Container &c, Index i) {
    return c[i]; //auto使用模板推导，无法推导出引用类型
}

template<typename Container, typename Index>
decltype(auto) getElem(Container &c, Index i) {
    return c[i]; //decltype(auto)可以正确推导出引用类型
                 //c++14写法
                 //传不了右值容器，仍需改进
}

template<typename Container, typename Index>
decltype(auto) getElem_forward(Container &&c, Index i) {
    // return c[i]; //与下等价，转发并未进行
    return std::forward<Container>(c)[i]; // 完美转发
    // return std::forward<decltype(c[i])>(c[i]);
}

std::vector<int> getVec() {
    return {10, 20, 30};
}

struct Point {
    int x;
    int y;
    Point &operator=(Point p) {
        x = p.x;
        y = p.y;
        std::cout << "operator= has worked" << std::endl;
        return *this;
    }
};

int main() {
    int a = 69;
    int *pa = &a;
    int &ra = a;
    int rra = std::move(a);
    decltype(pa) aaa;//括号内存放任意变量或者表达式，观察推导类型
    decltype(*pa + 10) aaaa; // decltype(*pa) 推导为 int&，加上10后推导为int

    const int ca = 91;
    const int *pca = &ca;
    const int &rca = ca;
    // const int rrca = std::move(ca);
    int *const cpa = &a;
    const int *const cpca = &ca;
    10;
    decltype(10) caaa;

    "hello world";
    int arr[2] = {0, 1};
    int (*arrp)[2] = &arr;
    int (&arrref)[2] = arr;
    decltype(arr) arraa;

    // fun1;
    // fun1p = &fun1;
    // fun2(10, fun1p);
    // decltype(fun2) fun1aa;

    decltype(fun1(10, 20)) fun1aaa;//编译器仅仅分析表达式类型，并不会执行函数表达式

    std::vector<int> vec = {1, 2, 3};
    decltype(vec[1]) value = vec[1];//vec[1]为表达式, 推导为 int&
    std::vector<bool> vec2 = {true, false, true};
    decltype(vec2[1]) value2;//推导类型并非bool&，而是std::vector<bool>::reference,也不需要初始赋值
    std::vector<Point> vec3 = { {1,2}, {3,4}, {5,6} };
    decltype(vec3[1]) value3 = vec3[1];
    // getVal(vec, 1) = 99;
    // getVal(vec2, 1) = true;
    // getVal(vec3, 1) = Point{7, 8};
    // std::cout << vec2[1] << std::endl;

    Point point{9, 9};
    // getVal_error(vec, 1) = 88;//仅仅使用模板无法正确推导返回值类型为引用
    // getVal_error(vec2, 1) = true;
    // getVal_error(vec3, 1) = point;
    // std::cout << vec2[1] << std::endl;

    // getElem_error(vec, 1); //实际返回右值
    // // getElem_error(vec, 1) = 77;
    // getElem_error(vec2, 1) = true;//vector<bool>::reference可以正确处理赋值
    // getElem_error(vec3, 1) = point;
    // std::cout << vec2[1] << std::endl;

    //正确使用decltype(auto)推导返回值类型为引用，从而可以进行赋值操作
    getElem(vec, 1) = 66;
    getElem(vec2, 1) = true;
    getElem(vec3, 1) = point;
    std::cout << vec3[1].x << std::endl;

    decltype(auto) mmm = getElem_forward(getVec(), 1);
    decltype(auto) nnn = getElem_forward(vec, 1);
    // getElem_forward(getVec(), 1) = 55; //无法对右值进行赋值操作
    nnn = 44;
    std::cout << nnn << std::endl;

    std::cout << "return done" << std::endl;
    return 0;
}