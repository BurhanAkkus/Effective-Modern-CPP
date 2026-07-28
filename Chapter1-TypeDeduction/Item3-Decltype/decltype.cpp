#include <iostream>
using namespace std;

template<typename T>
void printType(const char* name) {
    cout << name << " has type: " << __PRETTY_FUNCTION__ << "\n";
}
#define SHOW(x) printType<decltype(x)>(#x)
decltype(auto) f1()
{
int x = 0;
return x; // decltype(x) is int, so f1 returns int
}
decltype(auto) f2()
{
int x = 0;
return (x); // decltype((x)) is int&, so f2 returns int&
}
int main(){
    decltype(auto) c = f1();
    decltype(auto) c2 = f2();
    SHOW(c);
    SHOW(c2);
}