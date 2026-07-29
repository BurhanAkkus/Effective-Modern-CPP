#include <iostream>
#include <vector>
using namespace std;

vector<size_t> zeroToN(size_t n){
    vector<size_t> v;
    for(size_t i = 0; i < n; i++){
        v.push_back(i);
    }
    return v;
} 
int main(){
    enum Color { black, white, red }; 
    //auto white = false; // Compile Error, name white clashes with Color white! error: ‘auto white’ redeclared as different kind of entity
    enum class Color2 {brown, yellow,gray};
    auto gray = 5; // No clash with scoped enum

    Color c = red; // Fine.
    //Color2 c = grey; // Compile Error! grey undefined
    Color2 d = Color2::brown; // Fine
    auto e = Color2::yellow; // Fine

    // Enums have underlying types.
    // Unscoped enums implicitly convert -> integral types -> floating point
    if(c < 14.5){
        auto v {zeroToN(c)};
        for(auto& e:v){
            cout << e << " ";
        }
    } 
    // Scoped enums are strongly typed.
    // if(d < 14.5){ // Compile Error! Color2 < double??
    //     auto v {zeroToN(d)}; // Compile Error! Color2 -> size_t??
    //     for(auto& e:v){
    //         cout << e << " ";
    //     }
    // }

    //enum unscopedEnumsCantBeForwardDeclared;// Compile Error!
    enum class scopedEnumsCanBeForwardDeclared;// Fine;
    enum unscopedEnumsCanBeForwardDeclaredWithUnderlyingTypes: size_t;// Fine after C++11
}
// To get the underlying value for each enum value.
template<typename E>
constexpr auto toUType(E enumerator) noexcept{
    return static_cast<std::underlying_type_t<E>>(enumerator);
}
