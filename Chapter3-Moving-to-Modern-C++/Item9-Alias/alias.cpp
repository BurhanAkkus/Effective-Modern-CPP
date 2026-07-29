#include <iostream>
#include <memory> //unique_ptr
#include <unordered_map>
#include <string>
using namespace std;

typedef unique_ptr<std::unordered_map<std::string, std::string>>UPtrMapSS;
using UPtrMapSSAlias = unique_ptr<std::unordered_map<std::string, std::string>>;

typedef void (*FP)(int, const std::string&);
using FP = void (*)(int, const std::string&);

// Use Alias whenever possible. No drawbacks!.
// Allows templatization
int main(){

}