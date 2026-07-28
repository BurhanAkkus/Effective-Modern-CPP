#include <iostream>
using namespace std;
int main(){
    int x = 55;
    char& rx = (char&)x;
    char c = x; // copy
    char& rc = c;
    cout << x <<  " " << rx <<  " " << c << " " << rc;
}