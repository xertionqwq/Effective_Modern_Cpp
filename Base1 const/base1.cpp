#include <iostream>

int main() {
    const int a = 10;
    int const a01 = 10;
    int b = a;
    const int *p4 = &a;

    const int *const p = new int(10);
    //*p = b;错误
    //p = &b;错误
    //int *p1 = p;
    const int *p2 = p;
    //int *const p3 = p;

    const int &r1 = 10;//等号右侧可以接任何值,不论常量还是变量
    const int &r2 = a;
    int c = r2;//只进行赋值，没有内存操作
    int &r3 = r1;//r1 为 const int r1
}
