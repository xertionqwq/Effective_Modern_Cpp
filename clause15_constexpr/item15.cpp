#include <iostream>
#include <vector>
#include <string>

int get_value()
{
    return 10;
}

constexpr void func()
{
    int a = 99;
}

// 参数不用constexpr修饰，便于退化为普通函数
constexpr int abs_(int x)
{
    int test = 99;
    if (x > 0)
    {
        return x;
    }
    else
    {
        return -x;
    }

    // return x > 0 ? x : -x; // c++11仅支持一个返回语句，并且可使用非常量表达式
}
// constexpr int add_(int x) {
//     return x++;
//     return ++x;
// }

class A
{
public:
    constexpr A() : x1(5)
    {
        std::cout << "A()" << std::endl;
    }
    constexpr A(int i) : x1(i) {}
    // c++11该函数具有const属性了
    constexpr int get()
    {
        // x1 = 911;
        return x1;
    }
    ~A() = default;

    int x1;
};

// 编译期即可完成点的计算，增加效率
class Point
{
public:
    constexpr Point(double xVal = 0, double yVal = 0) noexcept
        : x(xVal), y(yVal)
    {
    }
    constexpr double xValue() const noexcept { return x; }
    constexpr double yValue() const noexcept { return y; }

    constexpr Point(Point &&p) : x(p.x), y(p.y)
    {
        p.x = 0;
        p.y = 0;
    }

    constexpr void setX(double newx) { x = newx; }
    constexpr void setY(double newy) { y = newy; }

private:
    double x;
    double y;
};
// 返回p相对原点的对称点
constexpr Point reflection(const Point &p) noexcept
{
    Point result;
    result.setX(-p.xValue());
    result.setY(-p.yValue());
    return result;
}
// 返回p1和p2的中点
constexpr Point midPoint(const Point &p1, const Point &p2) noexcept
{
    Point res;
    res.setX((p1.xValue() + p2.xValue()) / 2);
    res.setY((p1.yValue() + p2.yValue()) / 2);
    return res;
}

void check()
{
    if constexpr (sizeof(double) > sizeof(char))
    {
        std::cout << ">";
    }
    else
    {
        std::cout << "<";
    }
}

int main()
{
    int e = 10;
    const int a = 9;
    const int b = 1 + 3;
    const int c = a;
    constexpr int ca = 91;
    constexpr int cb = ca;
    constexpr int cc = c;
    int arr[e]; // gcc编译通过，MVSC会报错

    constexpr int fa = abs_(ca);
    int ee = abs_(e); // 发生退化

    constexpr A aaa{abs_(ca)}; // 必须使用常量表达式初始化
    A aab{8};
    // int get = aaa.get();
    // constexpr int mmm = aaa.get();

    constexpr Point p1{3.5, 9.1};
    constexpr Point p2{6.9, 5.8};
    // 编译期完成对res的计算
    constexpr Point res1{reflection(p1)};
    constexpr Point res2 = midPoint(p1, p2);
    Point res3 = midPoint(res1, res2); // 发生退化

    std::cout << "return done" << std::endl;
    return 0;
}