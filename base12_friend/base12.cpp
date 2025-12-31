#include <iostream>
#include <string>

namespace space1
{
    class Judy
    {
    public:
        Judy() = default;
        Judy(int x) : bed(x) {}
        // 客厅, 对外开放
        void drawingRoom()
        {
            std::cout << "Judy::drawingRoom" << std::endl;
        }
        friend void Jim(Judy &judy); // 男友jim可访问卧室

    private:
        // 卧室, 隐私
        void bedRoom()
        {
            std::cout << "Judy::bedRoom" << std::endl;
        }

        int bed = 1;
    };

    void Jim(Judy &judy)
    {
        //  全局友元函数
        std::cout << "function friend" << std::endl;
        judy.bedRoom(); // 访问卧室
        judy.bed = 2;   // 访问床
        std::cout << "bed: " << judy.bed << std::endl;
    }
}

namespace space2
{
    class Judy
    {
    public:
        Judy() = default;
        Judy(int x) : bed(x) {}
        void drawingRoom()
        {
            std::cout << "Judy::drawingRoom" << std::endl;
        }
        friend class Jim;

    private:
        void bedRoom()
        {
            std::cout << "Judy::bedRoom" << std::endl;
        }

        int bed = 1;
    };

    class Jim
    {
    public:
        Jim()
        {
            // 友元类
            std::cout << "class friend" << std::endl;
            judy.bedRoom();
            judy.bed = 2;
            std::cout << "bed: " << judy.bed << std::endl;
        }

    private:
        Judy judy;
    };
}

namespace space3
{
    // 前置声明 Judy：告诉编译器 Judy 是一个类，满足 Jim 类中指针/引用的类型依赖
    class Judy;

    class Jim
    {
    public:
        void visit();

    private:
        Judy *judy;
    };

    class Judy
    {
    public:
        Judy() = default;
        Judy(int x) : bed(x) {}
        void drawingRoom()
        {
            std::cout << "Judy::drawingRoom" << std::endl;
        }
        friend void Jim::visit(); // 此时 Jim 已声明，可正常声明友元

    private:
        void bedRoom()
        {
            std::cout << "Judy::bedRoom" << std::endl;
        }

        int bed = 1;
    };

    void Jim::visit()
    {
        std::cout << "class function friend" << std::endl;
        judy = new Judy(); // 指针初始化（也可通过构造函数初始化）
        judy->bedRoom();
        std::cout << "Jim 访问 Judy 的私有成员 bed：" << judy->bed << std::endl;
        delete judy; // 释放内存，避免内存泄漏
    }
}

int main()
{
    std::cout << "space1==========" << std::endl;
    space1::Judy judy_;
    space1::Jim(judy_);
    std::cout << std::endl;

    std::cout << "space2==========" << std::endl;
    space2::Judy judy__;
    space2::Jim jim__;
    std::cout << std::endl;

    std::cout << "space3==========" << std::endl;
    space3::Jim jim;
    jim.visit();
    std::cout << std::endl;

    std::cout << "return done" << std::endl;
    return 0;
}