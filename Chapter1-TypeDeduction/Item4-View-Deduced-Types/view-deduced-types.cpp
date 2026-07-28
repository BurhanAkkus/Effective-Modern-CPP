#include <iostream>
#include <boost/type_index.hpp>
using namespace std;

template<typename T> // declaration only for TD;
class TD;

// use f to get the runtime type of anything!.
template<typename T>
void f(const T& param)
{
using std::cout;
using boost::typeindex::type_id_with_cvr;
// show T
cout << "T = "
<< type_id_with_cvr<T>().pretty_name()
<< '\n';
// show param's type
cout << "param = "
<< type_id_with_cvr<decltype(param)>().pretty_name()
<< '\n';
}
int main(){
    const int theAnswer = 42;
    auto x = theAnswer;
    auto y = &theAnswer;
    //TD<decltype(x)> xType; // elicit errors containing the type in compile time.
    //TD<decltype(y)> yType;
    
}