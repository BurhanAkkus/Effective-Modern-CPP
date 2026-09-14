#include <iostream>
#include <memory>
#include <unordered_map>

using namespace std;

class Widget{
    public:
    long id;
    std::unique_ptr<Widget> loadWidget(long id){
        for(int i = 0; i < 1000000; i++);
        return make_unique<Widget>(new Widget{id});
    };

    shared_ptr<Widget> fastLoadWidget(long id){
        static unordered_map<long,weak_ptr<Widget>> cache;
        auto cachedWidgetPointer = cache[id].lock();
        if(!cachedWidgetPointer){ // not in cache!
            cachedWidgetPointer = loadWidget(id);
            cache[id] = cachedWidgetPointer;
        }
        return cachedWidgetPointer;
    }
};



int main(){
    shared_ptr<long> spl{new long(3L)};
    weak_ptr<long> wpl{spl};
    cout << "Size of shared ptr: " << sizeof(spl) << ". Pointee value: " << *spl<< endl;
    cout << "Size of weak ptr: " << sizeof(wpl) << ". Pointee value: " << *wpl.lock() <<endl;
    // spl points to different. wpl is dangling.
    spl.reset();
    // Undefined Behavior!
    //cout << "Pointee value when only pointer: " << *wpl.lock() <<endl;
    auto sp = wpl.lock();
    cout << "Pointee value when only pointer: " << (sp ? to_string(*sp) : "nulptr") <<endl;
    //shared_ptr<long> spl2{wpl}; Throws bad weak pointer
}