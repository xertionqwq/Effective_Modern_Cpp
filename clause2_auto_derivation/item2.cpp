#include<iostream>
#include<vector>
#include<string>

template<typename T>
void fT(T&& param){
    std::cout << typeid(param).name() << std::endl;
}

void fAuto(auto&& param){
    std::cout << typeid(param).name() << std::endl;
}

template <typename T>
void f1(T param){

}

template <typename T>
void f2(std::initializer_list<T> param){
    for (const auto &elem : param){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// auto createInitList(){
//     return {1, 2, 3};
// }

auto return10() {
    return 10;
}

auto Vec() {
    return std::vector<int>(10, 1);
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
    fT(rrefa);//括号内摆放此前任意一个变量或常量，观察推导类型
    fAuto(std::move(a));//括号内摆放此前任意一个变量或常量，观察推导类型   

    auto x = 27;
    auto x1(27);
    auto x2{27};//上述三种均为int
    auto x3 = {27};//std::initializer_list<int>
    auto y = {91, 69};//std::initializer_list<int>
    //auto z{91, 69};//error，无法推导出唯一类型

    //f1({11, 69, 91});//无法识别未std::initializer_list的参数列表
    f2({11, 69, 91});//正确识别为std::initializer_list参数

    std::cout  << "return done!" << std::endl;
    return 0;
}