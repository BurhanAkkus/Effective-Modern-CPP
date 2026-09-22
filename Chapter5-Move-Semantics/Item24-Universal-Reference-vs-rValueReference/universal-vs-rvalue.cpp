#include <iostream>
using namespace std;
class Widget{
    public:
    int x;
    Widget(int x):x{x}{};
};

ostream& operator<<(ostream& os, Widget w){
    os << w.x;
    return os;
}


void log(const Widget& w){
    cout << "lValueLog: "<< w << endl;
}

void log(Widget&& w){
    cout <<  "rValueLog: " << w << endl;
}

template<typename T>
void logForward(T&& t){
    cout << "Universal Reference: ";
    log(forward<T>(t));
}

int main(){
    Widget w{5};
    auto&& wLValueReferenceAuto = w; // Universal Reference
    auto&& wRValueReferenceAuto = move(w); // Universal Reference

    Widget w2{7};
    Widget& lValueReference = w;
    Widget&& rValueReference = move(w2);

    Widget w3{8};
    //Widget& lValueReference2 = move(w3); // compile error: cannot bind non-const lvalue reference to rvalue
    //Widget&& rValueReference2 = w3; // compile error: cannot bind rvalue reference to lvalue

    cout << "Universal Reference LogForward:" << endl;
    logForward(w);
    logForward(Widget{1});

    cout << "Log:" << endl;
    log(lValueReference);
    log(Widget{2});
}
