#include <string>
#include <iostream>
using namespace std;

class Widget{
    public:
    string s;
    Widget(const string text):s{move(text)}{};
    // text is const. uses copy constructor.
};

int main(){
    string s = "Darari";
    Widget w{s};
    cout << s << endl << w.s;
}