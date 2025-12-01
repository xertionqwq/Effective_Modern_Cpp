#include<iostream>
#include<vector>

struct A
{
public:
    A(){ std::cout << "A()" << std::endl; }

    // A(int a): a(a) {
    //     std::cout << "A(int a)" << std::endl;
    // }

    A(int b, int c) {
        std::cout << "A(int b, int c)" << std::endl;
    }

    A(const A& a): a(a.a){
        std::cout << "A(const A& a)" << std::endl;
    }
    // A(A&& a) noexcept : a(a.a){
    //     std::cout << "A(A&& a)" << std::endl;
    // }

    int a;
};

struct B{
public:
    B() { std::cout << "B()" << std::endl; }
    B(int b, int c) : b(b), c(c) {
        std::cout << "B(int b, int c)" << std::endl;
    }
    B(const B &b) {
        std::cout << "B(const B &b)" << std::endl;
    };

    int b;
    int c;
};

void fun1(A param) {
    std::cout << "fun1 with A param" << std::endl;
}

A fun2() {
    A a(5, 10);
    return a;
}

int main(){
    // A a = 10;
    // A b(10);
    // A c = (10);
    // A d{10};
    // A e = {10};

    // A f = 10, 5;
    // A g(10, 5);
    // A i{10, 5};
    // A j = {10, 5};
    fun1(A{10, 5});

    std::cout << "return done" << std::endl;
    return 0;
}