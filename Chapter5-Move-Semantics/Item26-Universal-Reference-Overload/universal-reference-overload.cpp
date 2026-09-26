#include <string>
#include <set>
#include <iostream>
#include <array>
std::set<std::string> names;
std::array<std::string,25> namesArray;

template<typename T>
auto logAndAdd(T&& name){
    std::cout<< "Log" << std::endl;
    names.emplace(std::forward<std::string>(name));
}

auto logAndAdd(unsigned int idx){
    std::cout << "Int OVerload Log" << std::endl;
    names.emplace(namesArray[idx]);
}

int main(){
    std::string darari{"Darari"};
    logAndAdd(darari);
    logAndAdd("Barari");
    logAndAdd(std::string{"Barari"});

    logAndAdd(22); // calls int overload.
    short nameIdx{1};
    logAndAdd(nameIdx); //  error: no matching function for call to ‘forward<std::string>(int&)’
}