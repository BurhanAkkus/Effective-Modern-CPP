#include <iostream>

using namespace std;
int& getValue(){
    static int i = 4;
    return i;
}

void acceptsOnlyLValue(int& lvalue){
    return;
}

void acceptsAll(const int& lvalue){
    return;
}

void print(string& lvalue){
    cout << "lvalue: " << lvalue << endl;
}

void print(const string& lvalue){
    cout << "const lvalue: " << lvalue << endl;
}

void print(string&& rvalue){
    cout << "rvalue: " << rvalue << endl;
}

void print(const string&& rvalue){
    cout << "const rvalue: " << rvalue << endl;
}

void print(string* pointer){
    cout << "pointer address: " << pointer <<" pointee value: " << *pointer << endl;
}



int main(){
    getValue() = 8;
    cout << getValue() << endl;
    //acceptsOnlyLValue(6); // compile error: cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
    acceptsAll(6);
    string s = "Barari";
    print("Darari");
    print(s);
    print(&s);
}