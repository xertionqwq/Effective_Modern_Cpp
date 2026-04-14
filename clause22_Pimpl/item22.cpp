#include "widget.h"
#include <iostream>

int main() {

    {
        Widget w;
        Widget w2(std::move(w));
    }

    std::cout << "return done" << std::endl;
    return 0;
}