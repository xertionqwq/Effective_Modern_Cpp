#include<iostream>
#include<string>

using fun1xxx = bool(int, int);
using fun1ppp = bool (*)(int, int);
bool fun1(int a, int b){
    return a == b;
}
const bool cfun1(int a, int b) {
    return a == b;
}
bool (*const fun1p)(int a, int b) = &fun1;
// const bool (*fun2p)(int a, int b) = &fun1;
const bool (*fun2p)(int a, int b) = &cfun1;//这里const并非权限问题，在于返回值,即返回值不可修改

const fun1ppp fun2pp = &fun1;//而别名又不需要fun1为const，此处的const为变成权限修改，而非返回值
                             //因为返回值在fun1ppp中就已经声明为非const
//const fun1ppp cfun1p = &cfun1;//所以该处编译不通过
                                //若将fun1ppp声明为bool (*)(int, int);编译重新通过

//无论const位于何处，始终为顶层
template <class T>
void f(const T param);
template <class T>
void f1(T const param);

void fun(int a);
void fun(const int a);//顶层const不构成重载
void fun(int *p);
void fun(int *const p) {
    if (p != nullptr) {
        // p = new int(10);
    }
}

//可摆放pdf中所有模板类型，观察模板推导
template <typename T>
void F(T param){
    std::cout << "F has worked " << param << std::endl;
}

int main() {
    int a{91};
    int *pa = &a;
    int &refa = a;
    int &&rrefa = std::move(a);

    const int ca{69};
    const int *pca = &ca;
    const int &refca = ca;
    const int &&rrefca = std::move(ca);
    int *const cpa = &a;
    const int *const cpca = &ca;
    23;
    F(cpca);//括号内摆放此前任意一个变量或常量，观察推导类型

    int arr[2] = {0, 1};
    "hello world";
    int (*arrp)[2] = &arr;
    int (&arrref)[2] = arr;
    F("hello world");

    fun1;
    cfun1;
    bool (*funptr)(int,int) = &fun1;
    bool (&funref)(int,int) = fun1;
    F(funref);

    std::cout << "return done" << std::endl;
    return 0;
}