#include <iostream>
#include <vector>
#include <string>
#include <memory>

// 7- 开始
class Widget;
std::vector<std::shared_ptr<Widget>> processedWigets;

// class Widget{
// public:
//     void process() {
//         // 2. emplace_back()调用shared的构造函数, 使用裸指针, 再次创建了control block
//         processedWigets.emplace_back(this);
//     }
// };

// 解决两次释放问题
// 但在面对非指针对象(栈内存)仍会存在问题
// 使用CRPT奇异递归模板
// class Widget : public std::enable_shared_from_this<Widget> {
// public:
//     void process() {
//         processedWigets.emplace_back(shared_from_this());
//     }
// };

class Widget : public std::enable_shared_from_this<Widget>
{
public:
    template <typename... Ts>
    // 提供静态函数
    static std::shared_ptr<Widget> create(Ts &&...params)
    {
        return std::shared_ptr<Widget>(new Widget(std::forward<Ts>(params)...));
    }

    void process()
    {
        processedWigets.emplace_back(shared_from_this());
    }

private:
    // 构造函数私有化
    Widget(int data) : _data(data) {}

    int _data;
};

// 7- 结束

int main()
{
    // 多次释放导致错误
    // {
    //     auto pt = new int(69);
    //     std::shared_ptr<int> spt1(pt);
    //     std::shared_ptr<int> spt2(pt);
    // }

    // 使用拷贝构造
    {
        std::shared_ptr<int> spt1(new int{91});
        std::shared_ptr<int> spt2(spt1);
    }

    // {
    //     // 1. 使用std::make_shared->构建control block
    //     auto w = std::make_shared<Widget>();
    //     w->process();
    // }

    // {
    //     // 使用栈而非堆的类对象
    //     auto w = Widget{};
    //     w.process();
    // }

    {
        auto w = Widget::create(1);
        w->process();
    }

    std::cout << "return done" << std::endl;
    return 0;
}