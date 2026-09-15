#include "widget.h"
#include <string>
#include <vector>

struct Widget::Impl{
    std::string name;
    std::vector<double> data;
};
Widget::Widget():pImpl(std::make_unique<Impl>()) {};
Widget::~Widget() = default;

Widget& Widget::operator=(Widget&&) = default;
Widget::Widget(Widget&&) = default;

Widget& Widget::operator=(const Widget& rhs){
    if (this != &rhs) *pImpl = *rhs.pImpl;
    return *this; 
};
Widget::Widget(const Widget& rhs):pImpl(std::make_unique<Widget::Impl>(*rhs.pImpl)){};