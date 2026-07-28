#include <iostream>
using namespace std;

// Case1: ParamType is a Reference or Pointer, but not a Universal Reference:
template<typename T>
void f1(T& param){
    (void)param;
    cout << "Case1: Param is a reference\n";
    cout << "__func__: " << __func__ << "\n";
    cout << "__PRETTY_FUNCTION__ : "<< __PRETTY_FUNCTION__ << "\n";  
}

template<typename T>
void f1_2(const T& param){
    (void)param;
    cout << "Case1: Param is a const reference\n";
    cout << "__func__: " << __func__ << "\n";
    cout << "__PRETTY_FUNCTION__ : "<< __PRETTY_FUNCTION__ << "\n";  
}
template<typename T>
void f1_3(T* param){
    (void)param;
    cout << "Case1: Param is a pointer\n";
    cout << "__func__: " << __func__ << "\n";
    cout << "__PRETTY_FUNCTION__ : "<< __PRETTY_FUNCTION__ << "\n";  
}

// Case2: Param is a universal Reference:
template<typename T>
void f2(T&& param){
    (void)param;
    cout << "Case2: Param is a universal Reference:\n";
    cout << "__func__: " << __func__ << "\n";
    cout << "__PRETTY_FUNCTION__ : "<< __PRETTY_FUNCTION__ << "\n";  
}

//Case 3: ParamType is Neither a Pointer nor a Reference
// Pass by value. completely new object. copied in.
template<typename T>
void f3(T param){
    (void)param;
    cout << "Case3: Param is Neither a Pointer nor a Reference:\n";
    cout << "__func__: " << __func__ << "\n";
    cout << "__PRETTY_FUNCTION__ : "<< __PRETTY_FUNCTION__ << "\n";  
}
int main(){
    int x = 27; // x is an int
    const int cx = x; // cx is a const int
    const int& rx = x; // rx is a reference to x as a const int
    //int& const crx = x; -> reference is immutable already.
    //int& r5 = 5; -> can't bind reference to rvalue.
    int* px = &x;
    const int* const_px = &x;
    const int* const const_p_const_x = &x;
    int* const only_p_const = &x;
    const char name[] = "J. P. Briggs"; // name's type is const char[13]
    const char * ptrToName = name;

    // 1. If expr’s type is a reference, ignore the reference part.
    // 2. Then pattern-match expr’s type against ParamType to determine T.

    f1(x);// T = int
    f1(cx);//T = const int
    f1(rx);// T = const int
    //f1(5);//  cannot bind non-const lvalue reference of type ‘int&’ to an rvalue of type ‘int’
    f1(px);// T = int*
    f1(const_px);//  T = const int*
    f1(const_p_const_x);//   T = const int* const
    f1(only_p_const);//  T = int* const
    f1(name);// T = const char [13]
    f1(ptrToName);//  T = const char*

    f1_2(x);//  T = int
    f1_2(cx);// T = int
    f1_2(rx);// T = int
    f1_2(5);// T = int
    f1_2(px);// T = int*
    f1_2(const_px);// T = const int*
    f1_2(const_p_const_x);//  T = const int*
    f1_2(only_p_const);//  T = int*
    
    f1_2(name);//  T = char [13]
    f1_2(ptrToName);//   T = const char*
    
    // f1_3(x);// error: no matching function for call to ‘f1_3(int&)’
    // f1_3(cx);// error: no matching function for call to ‘f1_3(const int&)’
    // f1_3(rx);// error: no matching function for call to ‘f1_3(const int&)’
    // f1_3(5);// error: no matching function for call to ‘f1_3(int)’
    f1_3(px);// T = int
    f1_3(const_px);//  T = const int
    f1_3(const_p_const_x);//  T = const int
    f1_3(only_p_const);//  T = int
    
    f1_3(name);//  T = const char
    f1_3(ptrToName);//   T = const char

    // If expr is an lvalue, both T and ParamType are deduced to be lvalue
    // references. That’s doubly unusual. First, it’s the only situation in template
    // deduction where T is deduced to be a reference. Second, although
    // ParamType is declared using the syntax for an rvalue reference, its deduced
    // type is an lvalue reference.
    // If expr is an rvalue, the “normal” (i.e., Case 1) rules apply.

    f2(x);//  T = int&
    f2(cx);//T = const int&
    f2(rx);//  T = const int&
    f2(5);// T = int
    f2(px);//  T = int*&
    f2(const_px);//  T = const int*&
    f2(const_p_const_x);//  T = const int* const&. Preserves the const of pointer.
    f2(only_p_const);//  T = int* const&. Preserves the const of pointer.
    
    f2(name);// T = const char (&)[13]
    f2(ptrToName);//   T = const char*&

    // 1. As before, if expr’s type is a reference, ignore the reference part.
    // 2. If, after ignoring expr’s reference-ness, expr is const, ignore that, too. If
    // it’s volatile, also ignore that. (volatile objects are uncommon. They’re
    // generally used only for implementing device drivers. For details, see Item
    // 40.)

    f3(x);// T = int
    f3(cx);// T = int
    f3(rx);// T = int
    f3(5);// T = int
    f3(px);// T = int*
    f3(const_px);// const int*
    f3(const_p_const_x);//  const int*
    f3(only_p_const);//  int*
    f3(name);//  T = const char*
    f3(ptrToName);//  T = const char*
    
}