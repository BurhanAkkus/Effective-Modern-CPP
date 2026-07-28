#include <iostream>
#include <memory> // unique_ptr 
#include <string>
#include <iterator> // iterator_traits
#include <functional>
#include <vector>
#include <typeinfo> // typeid
using namespace std;

struct Widget{
    string message;
    public:
        void doWhateverThisWidgetDoes(){return;};
        bool operator<(const Widget& rhs) const{return message.size() < rhs.message.size();}
};

int outside_x; // Fine. Declared, initialized to default 0
int main(){

    int x; // Fine. Declared but not initalized. Accessing value is Undefined Behavior.
    cout << x << endl; // Prints a different value each time.
    cout << outside_x << endl; // Prints 0 each time.

    //auto y; // Fails. Auto requires initialization. |  error: declaration of ‘auto y’ has no initializer
    auto y = 5;
    cout << y << endl;

    // Function template to hold a closure. Instantiates std::function. Uses more memory than auto.
    std::function<bool(const std::unique_ptr<Widget>&, const std::unique_ptr<Widget>&)> derefUPLess = [](const std::unique_ptr<Widget>& p1,const std::unique_ptr<Widget>& p2){
         return *p1 < *p2; };
    // C++11. Same type as the closure => needs same amount of memory
    auto derefUPLess11 =  [](const std::unique_ptr<Widget>& p1, const std::unique_ptr<Widget>& p2){ return *p1 < *p2; };
    // C++14. Parameters are also auto. One might even say, full-auto.
    auto derefUPLess14 =  [](const auto& p1, const auto& p2){ return *p1 < *p2; };

    std::vector<int> v;
    unsigned sz = v.size(); // narrows std::vector<int>::size_type down to unsigned.
    // Problem on 64-bit machine: size_type is 64 bits (size_t) but unsigned stays 32 bits, so this truncates.
    auto szAuto = v.size(); // exactly std::vector<int>::size_type, whatever that is here.

    cout << "sizeof(sz)     = " << sizeof(sz) << " bytes\n";     
    cout << "sizeof(szAuto) = " << sizeof(szAuto) << " bytes\n"; 
    cout << "same type? " << (typeid(sz) == typeid(szAuto)) << endl;

    std::unordered_map<std::string, int> m;
    for (const auto& p : m){ // p is of type std::pair<const std::string, int> 
    }
    for (const std::pair<std::string, int>& p : m){ // p is missing the const on key. Creates temp object to solve. Silently slow...
    }
    // ToDo
    // benchmark the difference between these 2 loops.
    
}

// ==== Example Taken From the Book directly.
template<typename It> // algorithm to dwim ("do what I mean")
void dwim(It b, It e){ // for all elements in range from b to e
    while (b != e) {
        typename std::iterator_traits<It>::value_type currValue = *b;
         b = b.next();
    }
}
// C++11
template<typename It>
void dwimWithAuto(It b, It e){
    while (b != e) {
        auto currValue = *b; // compiler figures out the type for us.
        b = b.next();
    }
}

