#include <iostream>

using namespace std;


void f(int i){
    cout << "Called int f with :" << i << endl;
    return;
}

void f(bool i){
    cout << "Called bool f with :" << i << endl;
    return;
}

void f(void* i){
    cout << "Called void ptr f with :" << i << endl;
    return;
}


int main(){
    f(0); // Calls int f!
    //f(NULL); // Error! error: call of overloaded ‘f(NULL)’ is ambiguous
    f(nullptr); // Calls void ptr f
}