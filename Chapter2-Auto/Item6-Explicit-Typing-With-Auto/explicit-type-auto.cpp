#include <iostream>
#include <vector>
using namespace std;

struct Widget{
    string message;
    public:
        void doWhateverThisWidgetDoes(){return;};
        bool operator<(const Widget& rhs) const{return message.size() < rhs.message.size();}
};

std::vector<bool> features(const Widget& w){
    return vector<bool>(500,true);
};

void processWidget(const Widget& w, bool isHighPriority){
    cout << (isHighPriority? "HighPriority" : "LowPriority") << endl;
}
int main(){

    Widget w;
    bool highPriority = features(w)[5];
    processWidget(w, highPriority);

    auto highPriorityAuto = features(w)[5]; // vector<bool> is optimized to assign each element a single bit. vector<bool>[] returns special type vector<bool>::reference.
    processWidget(w,highPriorityAuto); // casts vector<bool>::reference to bool. Undefined Behavior.
    auto highPriorityAutoWithCast = static_cast<bool>(features(w)[5]);
    processWidget(w,highPriorityAutoWithCast); // casts vector<bool>::reference to bool. Undefined Behavior.
   
    // ToDo
    // benchmark the performance gain of vector<bool>::reference proxy class.
    // and find another proxy class to benchmark as well.
}