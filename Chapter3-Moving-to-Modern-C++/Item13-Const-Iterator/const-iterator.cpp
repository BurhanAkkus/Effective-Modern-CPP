#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Some containers might not have the .cbegin or .cend member functions.
template<typename C, typename V>
void findAndInsert(C& container,const V& targetVal,const V& insertVal) 
{ 
    using std::cbegin; // C++14
    using std::cend; //C++14
    auto it = std::find(cbegin(container), cend(container),targetVal);
    container.insert(it, insertVal);
}

/*
implementation of cbegin():
accepts the __cont as const T& -> reference to const container.
begin overloads on this type and returns a pointer to const.
template<typename _Container>
    [[__nodiscard__, __gnu__::__always_inline__]]
    constexpr auto
    cbegin(const _Container& __cont) noexcept(noexcept(std::begin(__cont)))
      -> decltype(std::begin(__cont))
    { return std::begin(__cont); }
*/

int main(){
    std::vector<int> values; 
    auto it = find(values.cbegin(),values.cend(), 1983); //cbegin and cend return const_iterator
    values.insert(it, 1998);
}