#include <cassert>
#include <iostream>
#include <vector>

template<typename Derived>
struct Base{
    void name() {
        static_cast<Derived *>(this)->impl();
    }
};

template<typename Derived>
void fun (Base<Derived> derived) {
    derived.name();
}

struct D1 : public Base<D1> {
    void impl() { std::cout << "D1:impl()" << std::endl; }
};
struct D2 : public Base<D2> {
    void impl() { std::cout << "D2:impl()" << std::endl; }
};

//CRTP中的基类模板
template <typename E>
class VecExpression {
public:
    //通过将自己static_cast成为子类，调用子类的对应函数实现实现静态多态
    double operator[](size_t i) const { return static_cast<E const&>(*this)[i];     }
    size_t size()               const { return static_cast<E const&>(*this).size(); }
 
};
//将自己作为基类模板参数的子类 - 对应表达式编译树中的叶节点
class Vec : public VecExpression<Vec> {
    std::vector<double> elems;
 
public:
    double operator[](size_t i) const { return elems[i]; }
    double &operator[](size_t i)      { return elems[i]; }
    size_t size() const               { return elems.size(); }
 
    Vec(size_t n) : elems(n) {}
 
    Vec(std::initializer_list<double>init){
        for(auto i:init)
            elems.push_back(i);
    }
 
    // 核心：接收任意VecExpression派生类（如VecSum），延迟计算的终点
    template <typename E>
    Vec(VecExpression<E> const& vec) : elems(vec.size()) {
        // 唯一的计算点：遍历表达式，一次性计算结果
        for (size_t i = 0; i != vec.size(); ++i) {
            elems[i] = vec[i]; // 调用vec的operator[]，实际是VecSum的operator[]
        }
    }
};
//将自己作为基类模板参数的子类 - 对应表达式编译树中的二元运算符输出的内部节点
//该结构的巧妙之处在于模板参数E1 E2可以是VecSum，从而形成VecSum<VecSum<VecSum ... > > >的嵌套结构，体现了表达式模板的精髓：将表达式计算改造成为了构造嵌套结构
template <typename E1, typename E2>
class VecSum : public VecExpression<VecSum<E1, E2> > {
    E1 const& _u;
    E2 const& _v;
public:
    VecSum(E1 const& u, E2 const& v) : _u(u), _v(v) {
        assert(u.size() == v.size());
    }
 
    double operator[](size_t i) const { return _u[i] + _v[i]; }
    size_t size()               const { return _v.size(); }
};
//对应编译树上的二元运算符，将加法表达式构造为VecSum<VecSum... > >的嵌套结构
template <typename E1, typename E2>
VecSum<E1,E2> const operator+(E1 const& u, E2 const& v) {
   return VecSum<E1, E2>(u, v);
}

int main() {
    Base<D1> derived1;
    Base<D2> derived2;
    D1 derived3;
    D2 derived4;
    fun(derived1);
    fun(derived2);
    fun(derived3); // fun()函数子类基类都能传
    fun(derived4);

    // 原文链接：https://blog.csdn.net/HaoBBNuanMM/article/details/109740504
    Vec v0 = {1.0, 1.0, 1.0}; //假设共有1000个向量
    Vec v1 = {2.0, 2.0, 2.0};
    Vec v2 = {3.0, 3.0, 3.0};
    Vec v = {4.0, 5.0, 6.0};

    // 构建表达式 v0 + v1 + v2，赋值给v3，编译阶段形成表达式树
    Vec v3 = v0 + v1 + v2; //使用Vec接收，则完成Vec的计算
    auto v4 = v0 + v1;
    auto v5 = v4 + v2;
    auto v10 = v5 + v;//使用auto不断形成二元节点
    std::cout << v10[0] << std::endl; //直到拿到结果才完成计算
                                      //可debug进行验证

    // 输出结算结果
    for (int i = 0; i < v3.size(); i ++) {
        std::cout <<" "<< v3[i];
    }
    std::cout << std::endl;

    std::cout << "return done" << std::endl;
    return 0;
}