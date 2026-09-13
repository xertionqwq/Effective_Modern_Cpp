#include <iostream>
#include <string>
#include <tuple>
// 未限定域枚举
enum Color
{
    red,
    block,
    blue // 作用域全局, 同名会报错
};
enum Mood
{
    sad,
    happy,
    // blue,
};

// 枚举类
enum class _Color
{
    red,
    block,
    blue
};
enum class _Mood
{
    sad,
    happy,
    blue,
};

enum class test
{
    a1 = 11,
    a2,
    a4
};

enum School : int;
class A
{
public:
    School paraSchool;
};
enum School : int
{
    student,
    teacher,
};

enum class _School;
class B
{
public:
    _School paraSchool;
};
enum class _School
{
    student,
    teacher,
};

using UserInfo =             // 类型别名, 详情见clause9
    std::tuple<std::string,  // 名字
               std::string,  // Email地址
               std::size_t>; // 声望
enum UserInfoFields
{
    uiName,
    uiEail,
    uiReputation
};
enum class UserInfoFieldsScoped
{
    uiName,
    uiEail,
    uiReputation
};

// c++11
template <typename E>
constexpr typename std::underlying_type<E>::type
toUType(E param) noexcept
{
    return static_cast<typename std::underlying_type<E>::type>(param);
} // 将枚举转为实现枚举的底层的值
// c++14
template <typename E>
constexpr std::underlying_type_t<E>
toUType_(E param) noexcept
{
    return static_cast<std::underlying_type_t<E>>(param);
}
template <typename E>
constexpr auto
toUType__(E param) noexcept
{
    return static_cast<std::underlying_type_t<E>>(param);
}

// c++17
// enum class Index : int
// {
//     null,
//     a,
//     b = 10
// };

// c++20
// const char *ColorToString(_Color c)
// {
//     switch (c)
//     {
//         using enum _Color;
//     case red:
//         return "red";
//     case block:
//         return "block";
//     case blue:
//         return "blue";
//     default:
//         return "";
//     };
// }

int main()
{
    int x = red; // 隐式转换
    std::cout << x << std::endl;

    if (x == sad)
    {
        std::cout << "error!" << std::endl;
    }

    // int xx = _Color::blue; // 隐式转换被禁止
    _Color xx = _Color::blue;
    // if (xx == _Mood::blue) {
    //     std::cout << "error!" << std::endl;
    // }

    UserInfo uInfo{"Jimin", "9991.com", 10};
    auto val = std::get<1>(uInfo); // 获取第一个字段, 不直观
    // std::cout << val << std::endl;
    auto val_ = std::get<uiName>(uInfo);
    auto val__ =
        std::get<static_cast<int>(UserInfoFieldsScoped::uiName)>(uInfo);
    auto value =
        std::get<toUType(UserInfoFieldsScoped::uiName)>(uInfo);

    // Index int1{1};
    // Index int1_{1};
    // Index int10{10};
    // int mm = static_cast<int>(int10); // 仅能显式转换
    // // int1 = 2;
    // // int c = int10;
    // std::cout << mm << std::endl;
    // std::cout << std::boolalpha << (int1 < int10) << std::endl;
    // if (int1 == int1_)
    // {
    //     std::cout << "equal" << std::endl;
    // }

    // std::cout << ColorToString(xx) << std::endl;

    std::cout << "return done" << std::endl;
    return 0;
}