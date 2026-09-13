#include "widget.h"
#include "gidget.h"
#include <iostream>

struct Widget::Impl{
    std::string name{"Impl"};
    Gidget gidget;
};

Widget::Widget() : pImpl(std::make_unique<Impl>()) {
    std::cout << "Widget created." << std::endl;
}

Widget::~Widget() {
    std::cout << "Widget destroyed." << std::endl;
}

Widget::Widget(Widget &&) = default;

Widget &Widget::operator=(Widget &&) = default;
