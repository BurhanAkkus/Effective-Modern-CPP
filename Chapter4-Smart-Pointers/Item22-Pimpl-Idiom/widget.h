#include <memory>


class Widget{
    public:
    Widget();
    ~Widget();
    Widget& operator=(Widget&&);
    Widget(Widget&&);
    Widget& operator=(const Widget& rhs);
    Widget(const Widget&);
    private:
    struct Impl;
    std::unique_ptr<Impl> pImpl;
};