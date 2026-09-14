#include <memory>
#include <iostream>
#include <vector>
// ToDo
// benchmark make_(shared | unique) vs (shared | unique)ptr{new

class Widget{
    public:
    long id;
    Widget(long id):id{id}{};
    Widget() = default;
};

void processWidget(std::shared_ptr<Widget> spw, int priority){return;}

int computePriority(){
    return 0;
};

using namespace std;
int main(){

    auto widgetDeleter = [](Widget* pw) { 
        cout << "deleting Widget: " << pw->id << endl;
        delete pw;
    };
    /* If runtime order is 
    1-> new Widget
    2-> computePriority
    3-> shared_ptr initialization
    When computePriority throws, Widget created at step 1 is leaked.
    */
    processWidget(std::shared_ptr<Widget>(new Widget), 
                computePriority());
    // Leak proof!
    processWidget(std::make_shared<Widget>(4),computePriority());
    // With customDeleters
    shared_ptr<Widget> spwc{new Widget(5),widgetDeleter};
    processWidget(spwc,computePriority()); // copies spw, slow
    processWidget(move(spwc),computePriority()); // moves spw, fast

    // Can't use make functions with custom deleters.
    unique_ptr<Widget, decltype(widgetDeleter)> upw(new Widget, widgetDeleter); 
    shared_ptr<Widget> spw(new Widget, widgetDeleter);
 
    // make functions use paranthesis initialization.
    auto upv = std::make_unique<vector<int>>(10, 20);
    cout << "Size of the vector created with make function: " << upv->size() << endl;
    auto initList = {10,20};
    auto upv2{make_unique<vector<int>>(initList)};
    cout << "Size of the vector created with make function using initList: " << upv2->size() << endl;
};
