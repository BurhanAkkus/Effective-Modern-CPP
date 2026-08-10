#include <iostream>

using namespace std;
int f(int x) throw(); // no exceptions from f: C++98 style
int f(int x) noexcept; // no exceptions from f: C++11 style 
// C++98 has to keep the call-stack of f in an unwindable state:
// Destruct all local objects and go back to the caller; until the exception is caught. - No exception in this case, only the first parent is needed.
// C++11 has the guarantee from the developer: No Exceptions will be thrown from this function.
// It doesn't need the unwindable stack 

// ToDo
// Benchmark this.