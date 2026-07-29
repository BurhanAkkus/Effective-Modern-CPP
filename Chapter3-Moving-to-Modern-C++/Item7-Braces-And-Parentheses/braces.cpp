#include <iostream>
#include <vector>
#include <atomic>
#include <string>
using namespace std;

struct Widget{
    public:
        Widget(){};
        Widget(int i, bool b){
            cout << "Widget Int and Bool constructor " << endl;
        }
        Widget(int i, double d){
            cout << "Widget Int and Double Constructor " << endl;
        }

    private:
    int x= 4; // Fine. Default value
    int y{14}; // Also fine. Default value;
    //int z(5); // ERROR! Parentheses initialization can't be used in non-static data members.
};


struct Widget2{
    public:
        Widget2(){};
        Widget2(int i, bool b){
            cout << "Widget2 Int and Bool constructor " << endl;
        }
        Widget2(string i, string d){
            cout << "Widget2 String and String Constructor " << endl;
        }
        
        Widget2(Widget i,Widget d){
            cout << "Widget2 Widget and Widget Constructor " << endl;
        }
        Widget2(initializer_list<string> d){
            cout << "Widget2 Initializer List Constructor String " << endl;
            for(auto element:d){
                cout << element <<" ";
            }
            cout << endl;

        }
        Widget2(initializer_list<double> d){
            cout << "Widget2 Initializer List Constructor Double" << endl;
            for(auto element:d){
                cout << element <<" ";
            }
            cout << endl;
        }
};


struct Widget3{
    public:
        Widget3(initializer_list<double> d){
            cout << "Widget3 Initializer List Constructor Double" << endl;
            for(auto element:d){
                cout << element <<" ";
            }
            cout << endl;
        }
};

vector<int> initializeVectorWithParens(int i,int j){
    return vector<int>(i,j);
}
vector<int> initializeVectorWithBraces(int i,int j){
    return vector<int>{i,j};
}

// Only works for T that is a container. Enough for this demo.
template<typename Container>
void printContainer(const string& label, const Container& c){
    cout << label << " size=" << c.size() << " contents: ";
    for(const auto& element : c){
        cout << element << " ";
    }
    cout << endl;
}

template<typename T, typename... Ts>
void doSomeWork1(Ts&&... params)
{
    T localObject(std::forward<Ts>(params)...);
    printContainer("doSomeWork1 parens ->", localObject);
}

template<typename T, typename... Ts>
void doSomeWork2(Ts&&... params)
{
    T localObject{std::forward<Ts>(params)...};
    printContainer("doSomeWork2 braces ->", localObject);
}

int main(){
    // 4 ways to initialize in C++11
    int x = 0; // Looks like assignment but is actually initialization.
    int y(0); // Initializes to 0
    int z{0}; // same
    int f = {0}; // same but redundant, uses '=' and {}braces together for no benefit.
    
    Widget w1; // Default constructor
    Widget w2 = w1; // Not assignment... calls copy constructor.
    w1 = w2; // assignment. calls copy operator=

    vector<int> v{ 1, 3, 5 }; // initial values

    atomic<int> ai1{ 160 }; // fine
    atomic<int> ai2(51); // fine
    //atomic<int> ai3 = 0; // error! can't assign to atomic | error: use of deleted function ‘std::atomic<int>::atomic(const std::atomic<int>&)’
    // !! This works in C++17.

    double dx, dy, dz;
    int sum1{ dx + dy + dz };  // Narrowing cast of runtime expressions is a warning.! warning: narrowing conversion of ‘((dx + dy) + dz)’ from ‘double’ to ‘int’. 
    //int sum1_1{ 1.0 + 3.7};  // Narrowing cast of a constant is an Error!  error: narrowing conversion of ‘4.7000000000000002e+0’ from ‘double’ to ‘int’ 
    int sum2( dx + dy + dz );  // Narrowing cast. Fine. Legacy code uses this.
    int sum3 = dx + dy + dz ;  // Narrowing cast. Fine. Legacy code uses this.

    Widget ww2(); // Most vexing parse! Declares a function w2 that returns a Widget.
    Widget w3{}; // Calls Widget ctor with no args.

    Widget w11(10, true); 
    Widget w12{10, true}; 
    Widget w13(10, 5.0); 
    Widget w14{10, 5.0}; 

    Widget2 w31(10, true); // uses parens and, as before, calls first ctor
    Widget2 w32{10, true}; // uses braces, but now calls std::initializer_list ctor (10 and true convert to string)
    Widget2 w35("Darari","Barari");// uses parens and calls string string constructor.
    Widget2 w36{"Darari","Barari"};// uses braces and calls initializer_list<string> constructor
    Widget2 w37{14.87,55};// casts second int to double
    Widget2 w38{w1,w2}; // Tries to call a initalizer_list, fails all of them, falls back to non-initializer-list ctors.

    Widget3 emptyInitializerList {};
    Widget3 emptyInitializerList2 ({});
    Widget3 emptyInitializerList3 {{},{},{}}; // passes a initializer_list with each {} being an element.

    auto object1 = initializeVectorWithParens(5,10);
    auto object2 = initializeVectorWithBraces(5,10);
    cout << "Size of object1: " << object1.size() << endl;
    cout << "Size of object2: " << object2.size() << endl;


    doSomeWork1<std::vector<int>>(10, 20);// initialized with parens
    doSomeWork2<std::vector<int>>(10, 20);// initialized with braces
}