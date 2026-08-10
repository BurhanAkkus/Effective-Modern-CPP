#include <iostream>
#include <memory>

class Base {
public:
virtual void doWork(); 
void doWork2();  // can't be overridden, must be virtual.
virtual void lValueFunction() &; // can be called only when this* is an lValue.
virtual void rValueFunction() &&;// can be called only when this* is an rValue.
};
class Derived: public Base {
public:
virtual void doWork(); // virtual here is optional. Include for self-documenting code.
                       // name must be identical.
                       // parameter types must be identical.
                       // constness must be identical.
                       // return types and exception specification must be identical.
                       // reference qualifiers must be identical. -> C++11 feature.
virtual void lValueFunction() &;
virtual void rValueFunction() &&;
};


class BaseExample {
public:
virtual void mf1() const;
virtual void mf2(int x);
virtual void mf3() &;
void mf4() const;
};
class DerivedExample: public BaseExample {
public:
virtual void mf1(); // Doesn't override - const difference.
virtual void mf2(unsigned int x); // Doesn't override - parameter type difference.
virtual void mf3() &&; // Doesn't override - reference qualifier difference.
void mf4() const; // Doesn't override - base function is not virtual.
};

// Doesn't compile
class DerivedExampleWithOverride: public BaseExample {
public:
// virtual void mf1() override; // mf1() marked ‘override’, but does not override
// virtual void mf2(unsigned int x) override; // mf2(unsigned int)’ marked ‘override’, but does not override
// virtual void mf3() && override; // mf3() &&’ marked ‘override’, but does not override
// virtual void mf4() const override; // mf4() const’ marked ‘override’, but does not override
};

/*
* override is a reserved word only when it occurs at the end of a member function declaration.
*/
