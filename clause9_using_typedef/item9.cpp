#include<iostream>
#include<vector>
#include<initializer_list>
#include<memory>
#include<type_traits>
#include<typeinfo>

struct A{
    using subType = int;//成员类型定义
};

struct B{
    static double subType;//成员变量定义
};

template<typename T>
class myClass{
public:
    void foo(){
        typename T::subType *ptr;
    }//typename用于告诉编译器T::subType是一个类型，而不是静态成员
};

template <typename T>
using myVec = std::vector<T>;//类型别名模板，推荐使用
template <typename T>
struct myVec1{
    typedef std::vector<T> type;
};//必须创建struct或class来包含typedef，不推荐使用
//template <typename T>
//typedef std::vector<T> myVec2;//error，不支持这种写法

template<>
class myVec1<float>{
public:
    enum class colorType {
        red,
        green,
        blue
    };
    colorType type;
};//特化版本

template<typename T>
class widget{
public:
    myVec<T> list;
};

template<typename T>
class widget1{
public:
    typename myVec1<T>::type list;
};

template<typename T>
class traits1{
public:
    void foo(){
        const int &rr = 10;
        typename std::remove_const<T>::type var1 = rr;
        typename std::remove_reference<T>::type var2 = rr;
    }
};

int main(){
    myClass<A> a;
    a.foo();
    myClass<B> b;
    //b.foo();//error，B::subType不是类型

    myVec<int> vec = {1, 2, 3, 4, 5};
    myVec1<int>::type vec1 = {6, 7, 8, 9, 10};//T已经推导出为int，不需要typename

    std::cout << "return done!" << std::endl;
    return 0;
}