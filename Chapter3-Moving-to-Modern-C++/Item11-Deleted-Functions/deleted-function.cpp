#include <iostream>

using namespace std;

template<typename T>
void processPointer(T* ptr);

template<>
void processPointer<void>(void*) = delete; // processPointer template can't be instantiated with void pointer.

template<>
void processPointer<char>(char*) = delete;// processPointer template can't be instantiated with char pointer.\

// Other decorators will also need to be removed to be sure :)
// Combinations of const and volatile.
// Kinda cumbersome so not written here. Also there should be a better way than doing the 2x2 matrix by hand...
template<>
void processPointer<const void>(const void*) = delete;// processPointer template can't be instantiated with const void pointer.
template<>
void processPointer<const char>(const char*) = delete;// processPointer template can't be instantiated with copnst char pointer.

bool isLucky(int number);
bool isLucky(char number) = delete; 
bool isLucky(double number) = delete; // Will catch floats too. C++ prefers casting floats to double over casting to int 
bool isLucky(bool number) = delete; 

bool isLucky2(int number);
template<typename T> bool isLucky2(T) = delete; // isLucky2 can't be called with any paramter type except int.


int main(){
    //isLucky(true); // error: use of deleted function ‘bool isLucky(bool)’
    //isLucky(3.5); //error: use of deleted function ‘bool isLucky(double)’
    //isLucky('a'); //error: use of deleted function ‘bool isLucky(char)
    float f = 1;
    //isLucky(f); // error: use of deleted function ‘bool isLucky(double)’
    isLucky(-1); // Compilation is ok. Fails on Link Time - no definition.
    unsigned u = 1;
    //isLucky(u); //error: call of overloaded ‘isLucky(unsigned int&)’ is ambiguous. Picking of function happens first. Then checks if the function is deleted.
    //isLucky2(u); // error: use of deleted function ‘bool isLucky2(T) [with T = unsigned int]’
    size_t t = 4;
    //isLucky(t); //error: call of overloaded ‘isLucky(size_t&)’ is ambiguous.  Picking of function happens first. Then checks if the function is deleted.
    //isLucky2(t); //error: use of deleted function ‘bool isLucky2(T) [with T = long unsigned int]’
    const unsigned cu = 4;
    //isLucky2(cu); //error: use of deleted function ‘bool isLucky2(T) [with T = unsigned int]’
}