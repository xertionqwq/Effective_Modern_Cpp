#include <iostream>
#include <memory>
#include <vector>

// 父类
class Investment{
public:
    virtual ~Investment() = default;
};

class Stock : public Investment{
public:
    Stock(int a) {
        std::cout << "Stock(int a)" << std::endl;
    }
    ~Stock() override {
        std::cout << "~Stock()" << std::endl;
    }
};

class Bond : public Investment{
public:
    Bond(int a, int b) {
        std::cout << "Bond(int a, int b)" << std::endl;
    }
    ~Bond() override {
        std::cout << "~Bond()" << std::endl;
    }
};

class RealEstate : public Investment{
public:
    RealEstate(int a, int b, int c) {
        std::cout << "RealEstate(int a, int b, int c)" << std::endl;
    }
    ~RealEstate() override {
        std::cout << "~RealEstate()" << std::endl;
    }
};

// 工厂函数
template<typename... Ts>
Investment *makeInvestment_test(Ts &&... params) {
    Investment *ptr = nullptr;
    constexpr size_t numParams = sizeof...(Ts);
    // 在栈上分配, 但是栈对象被销毁, 内存传不出来
    if constexpr (numParams == 1) {
        Stock stock = Stock(std::forward<Ts>(params)...);
        ptr = &stock;
    } else if constexpr (numParams == 2) {
        Bond bond = Bond(std::forward<Ts>(params)...);
        ptr = &bond;
    } else if constexpr (numParams == 3) {
        RealEstate realEstate = RealEstate(std::forward<Ts>(params)...);
        ptr = &realEstate;
    }
    return ptr;
}

template <typename... Ts>
Investment *makeInvestment_test2(Ts &&... pararms) {
    Investment *ptr = nullptr;
    constexpr size_t numParams = sizeof...(Ts);
    // 在堆上分配, 如果没有释放, 内存泄漏
    if constexpr (numParams == 1) {
        ptr = new Stock(std::forward<Ts>(pararms)...);
    } else if constexpr (numParams == 2) {
        ptr = new Bond(std::forward<Ts>(pararms)...);
    } else if constexpr (numParams == 3) {
        ptr = new RealEstate(std::forward<Ts>(pararms)...);
    }
    return ptr;
}

template <typename... Ts>
std::unique_ptr<Investment> makeInvestment(Ts &&... pararms) {
    std::unique_ptr<Investment> ptr{nullptr};
    constexpr size_t numParams = sizeof...(Ts);
    // 在堆上分配, 由unique_ptr管理, 不会内存泄漏
    if constexpr (numParams == 1) {
        ptr.reset(new Stock(std::forward<Ts>(pararms)...));
    } else if constexpr (numParams == 2) {
        ptr.reset(new Bond(std::forward<Ts>(pararms)...));
    } else if constexpr (numParams == 3) {
        ptr.reset(new RealEstate(std::forward<Ts>(pararms)...));
    }
    return ptr;
}

// 自定义删除器, 以便在删除对象时输出提示信息
auto delInvmt = [](Investment *pInvestment) {
    std::cout << "delete Investment" << std::endl;
    delete pInvestment;
};
template <typename... Ts>
std::unique_ptr<Investment, decltype(delInvmt)> // 更改后的返回类型 
makeInvestment2(Ts &&... pararms) {
    std::unique_ptr<Investment, decltype(delInvmt)> ptr{nullptr, delInvmt};
    constexpr size_t numParams = sizeof...(Ts);
    // 在堆上分配, 由unique_ptr管理, 不会内存泄漏
    if constexpr (numParams == 1) {
        ptr.reset(new Stock(std::forward<Ts>(pararms)...));
    } else if constexpr (numParams == 2) {
        ptr.reset(new Bond(std::forward<Ts>(pararms)...));
    } else if constexpr (numParams == 3) {
        ptr.reset(new RealEstate(std::forward<Ts>(pararms)...));
    }
    return ptr;
}


template <typename... Ts>
auto makeInvestment3(Ts &&... pararms) { // c++14
    // 删除器定义在函数里
    auto delInvmt2 = [](Investment *pInvestment) {
        std::cout << "delete Investment" << std::endl;
        delete pInvestment;
    };
    std::unique_ptr<Investment, decltype(delInvmt2)> ptr{nullptr, delInvmt2};
    constexpr size_t numParams = sizeof...(Ts);
    // 在堆上分配, 由unique_ptr管理, 不会内存泄漏
    if constexpr (numParams == 1) {
        ptr.reset(new Stock(std::forward<Ts>(pararms)...));
    } else if constexpr (numParams == 2) {
        ptr.reset(new Bond(std::forward<Ts>(pararms)...));
    } else if constexpr (numParams == 3) {
        ptr.reset(new RealEstate(std::forward<Ts>(pararms)...));
    }
    return ptr;
}



int main() {

    std::cout << "return done" << std::endl;
    return 0;
}