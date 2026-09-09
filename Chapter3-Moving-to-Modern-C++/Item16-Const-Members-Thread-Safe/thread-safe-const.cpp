#include <iostream>
#include <vector>
#include <mutex> 
class Polynomial{
    using RootsType = std::vector<double>;
    private:
        RootsType calculateRoots() const // const signals calculateRoots is a read operation, it doesn't modify the Polynomial.
        {
            std::call_once(rootsComputed,[this]{
                roots = {1, 3};
            });
            return roots;
        }; 
        mutable std::once_flag rootsComputed;
        mutable RootsType roots{};
};

int main(){
    return 0;
}

/*
    Overall message of this item is that const member functions should be thread safe.
*/