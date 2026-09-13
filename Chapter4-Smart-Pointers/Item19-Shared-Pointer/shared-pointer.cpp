#include <iostream>
#include <memory>
#include <vector>
using namespace std;
    // ToDo
    // benchmark difference between move vs copy ctor/assign.
    // benchmark make_shared initialization vs object initialization
int main(){
    long l = 123L;
    long* lp = &l;
    shared_ptr<decltype(l)> spl{make_shared<long>(6)};
    shared_ptr<decltype(l)> spl2{make_shared<long>(l)};
    cout << "size of long: " << sizeof(l) << endl;
    cout << "size of long pointer: " << sizeof(lp) << ". Pointee value: " << *lp << endl;
    cout << "size of shared pointer of long: " << sizeof(spl) << ". Pointee value: " << *spl << endl;
    cout << "size of shared pointer of already existing long: " << sizeof(spl2) << ". Pointee Value: " << *spl2 << endl;

    auto customDeleter1 = [](long* lp){
        cout<< "CustomDeleter1 deleting: " << (lp ? to_string(*lp) : "nullptr") << endl;
        delete lp;
    };
    auto customDeleter2 = [](long* lp){
        cout<< "CustomDeleter2 deleting: " << (lp ? to_string(*lp) : "nullptr") << endl;
        delete lp;
    };
    shared_ptr<long> spcd1(new long{1L},customDeleter1);
    shared_ptr<long> spcd2(new long{2L},customDeleter2);
    // Unrelated -> vector starts deleting from the beginning.
    // spcd1 and spcd2 are COPIED into v. so 1L and 2L have 2 shared ptrs that point to them.
    vector<shared_ptr<long>> v{shared_ptr<long>(new long{3L},customDeleter2),spcd1,spcd2,shared_ptr<long>(new long{4L},customDeleter1)};
    shared_ptr<long> spcd3(nullptr,customDeleter2);
    shared_ptr<long> spcd4(new long{5L},customDeleter1);
    spcd3 = spcd4; // drops the previous control block, will destruct 5L with customDeleter1
    spcd1 = spcd2; 

    // when a shared pointer is initialized from a raw pointer
    // a new control block is created.
    // Initializing more than 1 shared ptr from the same raw pointer leads to UB on destruct time.
    //shared_ptr<long> sp3{lp};
    //shared_ptr<long> sp4{lp};
}


// use shared_from_this when you need to work with a shared ptr that points to this.
// Needs to have a shared ptr on the outside that points to the instance.
class Widget: public std::enable_shared_from_this<Widget> {
    long id;
    public:
    void process();
};

std::vector<std::shared_ptr<Widget>> processedWidgets;

void Widget::process() {
    processedWidgets.emplace_back(shared_from_this());
}