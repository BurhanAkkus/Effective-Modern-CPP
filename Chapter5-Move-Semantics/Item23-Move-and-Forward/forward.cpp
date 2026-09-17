#include <string>
#include <iostream>
using namespace std;

class Widget{
    public:
    string s;
};

void process(const Widget& lValue){
    cout << "Lvalue Process" << endl;
    return;
}

void process(Widget&& rValue){
    cout << "Rvalue Process" << endl;
    return;
}

template<typename T>
void logAndProcess(T&& val){
    cout << "Logging" << endl;
    process(forward<T>(val));
}

// Always calls the LValue process overload
// because val is a parameter, which is always an lvalue.
template<typename T>
void logAndProcessWithoutForward(T&& val){
    cout << "Logging" << endl;
    process(val);
}

int main(){
    Widget w{"Darari"};
    logAndProcess(w);
    logAndProcessWithoutForward(w);
    logAndProcess(move(w));
    logAndProcessWithoutForward(move(w));
}
