#include <array>
#include <iostream>
#include <cassert>
using namespace std;

// C++14 feature. Compile error on C++11
// returns constexpr int if base and exp are themselves constexpr.
// returns int otherwise.
constexpr int pow(int base, int exp) noexcept{
    assert(exp >= 0);
    int product = 1;
    for(int i = 0; i < exp;i++){
        product *= base;
    }
    return product;
}
// C++11 style branching constexpr call.
constexpr int pow_c11(int base, int exp) noexcept
{
return (exp == 0 ? 1 : base * pow(base, exp - 1));
}


class Point {
public:
    constexpr Point(double xVal = 0, double yVal = 0) noexcept
    : x(xVal), y(yVal){}
    constexpr double xValue() const noexcept { return x; }
    constexpr double yValue() const noexcept { return y; }
    constexpr void setX(double newX) noexcept { x = newX; } // C++14
    constexpr void setY(double newY) noexcept { y = newY; } // C++14
private:
    double x, y;
};

constexpr Point midpoint(const Point& p1, const Point& p2) noexcept{
    return { (p1.xValue() + p2.xValue()) / 2, // call constexp member funcs
    (p1.yValue() + p2.yValue()) / 2 }; 
}

constexpr Point reflection(const Point& p) noexcept{
    Point result; // create non-const Point
    result.setX(-p.xValue()); // set its x and y values
    result.setY(-p.yValue());
    return result; // return copy of it
}


int main(){
    int sz = 7; // non-constexpr variable
    const auto c = sz;
    // constexpr variables must hold const values that are known at compile time
    //constexpr auto c2 = c; //  error: the value of ‘c’ is not usable in a constant expression
    //constexpr auto c2 = sz; // error: the value of ‘sz’ is not usable in a constant expression
    const int sz2 = 5;
    constexpr auto arraySize1 = sz2; // constexpr is implicitly const.
    //array<int, sz> data1; // error: the value of ‘sz’ is not usable in a constant expression
    array<int, sz2> data1; //fine, value of sz2 is known at compile time and is constant.
    constexpr auto arraySize2 = 10; // fine, 10 is a compile-time constant
    array<int, arraySize2> data2; // fine, arraySize2 is also known at compile time.
    array<int, sz2> data3; // fine, sz2 is also known at compile time.

    //  const floating-point types can't be read in evaluation of a constexpr until C++20.
    const double d = 3.14;
    constexpr double ced = 4.12;
    //constexpr auto ced = d; // error: the value of ‘d’ is not usable in a constant expression

    constexpr auto numConds = 5;
    array<int, pow(3, numConds)> results;
    int base,exp;
    cin >> base >> exp;
    auto baseToExp = pow(base, exp); // call pow function in runtime.
    auto baseToExp2{pow_c11(base,exp)};

    constexpr Point p1(9.4, 27.7);// fine. Runs constexpr ctor at compile time.
    constexpr Point p2(28.8, 5.3);
    //p1.setX(7); // error: passing ‘const Point’ as ‘this’ argument discards qualifiers
    
    constexpr auto mid = midpoint(p1, p2); // p1 and p2 are constexpr so midpoint returns constexpr.
    constexpr auto reflectedMid = reflection(mid); // mid is known at compile time, so is reflectedMid.
}