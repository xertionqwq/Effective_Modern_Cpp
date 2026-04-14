#include <memory>

class Widget{
public:
    Widget();
    ~Widget();
    Widget(Widget &&);
    Widget &operator=(Widget &&);

    // Widget();
    // ~Widget();
private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};