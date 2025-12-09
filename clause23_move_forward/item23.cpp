#include<iostream>
#include<vector>
#include<type_traits>

//std::move实际伪码实现
//将任何类型的左值强制转换为右值引用，从而允许资源的移动语义
template<typename T>
typename std::remove_reference<T>::type &&mymove(T &&param){
    using RTtype = typename std::remove_reference<T>::type &&;//c++11   
    return static_cast<RTtype>(param);
}

template<typename T>
decltype(auto) mymove2(T &&param){
    using RTtype = std::remove_reference_t<T> &&;//c++14
    return static_cast<RTtype>(param);
}

//由于引用折叠，左值并非强转为右值引用
template<typename T>
T &&my_move(T &&param) {
    return static_cast<T &&>(param);
}

struct A{
    A() {
        std::cout << "A default constructor called!" << std::endl;
    }
    A(int v):val(v){
        std::cout << "A create constructor called!" << std::endl;
    }
    A(const A &a) {
        std::cout << "A copy constructor called!" << std::endl;
        val = a.val;
    }
    A(A &&a) {
        std::cout << "A move constructor called!" << std::endl;
        val = a.val;
        a.val = 0;
    }

    int val;
};

class Annotation{
public:
    explicit Annotation(const A &a): a_param(std::move(a)) {
        // std::cout << "Annotation constructor called!" << std::endl;
    }

private:
    A a_param;
};

void process(const A& lval) {
    std::cout << "Lvalue processed" << std::endl;
}
void process(A&& rval) {
    std::cout << "Rvalue processed" << std::endl;
}

template<typename T>
void logAndProcess(T&& param) {
    // process(param); //始终调用左值
    // process(std::move(param)); // 始终调用右值
    process(std::forward<T>(param)); // 完美转发,保留参数值类型
}

int main() {
    int mmm = 10;
    int &rrm = my_move(mmm); // T is deduced to int&
    // int &&rrr = my_move(mmm); //出现引用折叠，T被推导为int&，最终结果是int&
    int &&rrr = my_move(20); // T is deduced to int
    int &&rrr1 = mymove(mmm);

    // Annotation aa{10};

    // const A bb{10};
    // const A cc = std::move(bb);

    // A a1{91};
    // A rra = std::move(a1);

    A aa{91};
    A bb{69};
    A rraa = mymove(aa);
    logAndProcess(bb);  //我们希望调用左值版本 
    logAndProcess(rraa);   //希望调用右值版本
    // logAndProcess(55);


    std::cout << "return done!" << std::endl;
    return 0;
}