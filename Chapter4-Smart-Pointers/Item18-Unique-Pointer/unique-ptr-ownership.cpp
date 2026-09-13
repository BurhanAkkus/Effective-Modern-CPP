#include <iostream>
#include <memory>
#include <functional>
#include <string>

using namespace std;

enum class Relationship{Family=0,Friend=1,Coworker=2};

class Tanidik{
    public:
    string name;
    int age;
    virtual ~Tanidik() = default;
    Tanidik(string name,int age):name{move(name)},age{age}{}
};
class Friend: public Tanidik{
    public:
    string hobby;
    Friend(string name,int age,string hobby):Tanidik{move(name),age},hobby{move(hobby)}{}
};
class Family: public Tanidik{
    public:
    string relation;
    Family(string name,int age,string relation):Tanidik{move(name),age},relation{move(relation)}{}

};
class Coworker: public Tanidik{
    public:
    string company;
    Coworker(string name,int age,string company):Tanidik{move(name),age},company{move(company)}{}

};

auto deleteTanidikLambda = [](Tanidik* tanidik){
    cout<< tanidik->name << " is now dead to me!" << endl;
    delete tanidik;
};

void deleteTanidikFunction(Tanidik* tanidik){
    cout<< tanidik->name << " is no longer important to me!" << endl;
    delete tanidik;
}

void deleteTanidikFunctionWithMoreState(Tanidik* tanidik, string deleteString){
    cout<< tanidik->name << deleteString << endl;
    delete tanidik;
}

template<typename ...Ts>
unique_ptr<Tanidik,decltype(deleteTanidikLambda)> meetSomeone(Relationship relationship,Ts&& ...args){
    unique_ptr<Tanidik,decltype(deleteTanidikLambda)> uptrTanidik(nullptr,deleteTanidikLambda);
    switch(relationship){
        case Relationship::Family: uptrTanidik.reset(new Family{forward<Ts>(args)...}); break;
        case Relationship::Friend: uptrTanidik.reset(new Friend{forward<Ts>(args)...}); break;
        case Relationship::Coworker: uptrTanidik.reset(new Coworker{forward<Ts>(args)...}); break;
        default: cout << "Invalid relationship!" << endl;
    }
    return uptrTanidik;
}

int main(){
    double d = 16.3;
    double* dp = &d;
    std::unique_ptr<double> uqd{std::make_unique<double>(3.3)};
    std::cout << "Size of Double: " << sizeof(d) << "\nSize of Double Pointer: " << sizeof(dp) <<"\nSize of unique pointer double: " << sizeof(uqd) << std::endl;
    // compare sizes of default destructor unique pointer with function unique pointer.
    auto upmyWife{meetSomeone(Relationship::Family,"Elulu",01,"wife")}; // Lambda destructor has no memory cost.
    auto upMyFather{make_unique<Family>(Family{"Darari",12,"father"})};
    unique_ptr<Tanidik,void(*)(Tanidik*)> upMyMother{new Family{"Barari",23,"mother"},deleteTanidikFunction}; // Function pointer in destructor adds 8 bytes.
    auto deleteTanidikBound{bind(deleteTanidikFunctionWithMoreState,placeholders::_1,string{" is history to me!"})};
    unique_ptr<Tanidik,decltype(deleteTanidikBound)> upMySister{new Family{"Sarari",34,"sister"},deleteTanidikBound}; // Bound string is stored inside the deleter.
    cout<< "Size of unique pointer with custom destructor: " << sizeof(upmyWife) << endl;
    cout << "Size of unique pointer with default destructor: " << sizeof(upMyFather) << endl;
    cout << "Size of unique pointer with function pointer deleter: " << sizeof(upMyMother) << endl;
    cout << "Size of unique pointer with stateful (bound) deleter: " << sizeof(upMySister)
         << " (8 + sizeof(deleter) = " << 8 + sizeof(deleteTanidikBound) << ")" << endl;
    // unique Pointer -> shared pointer conversion
    shared_ptr<Tanidik> upTeamLead{meetSomeone(Relationship::Coworker,"orari",22,"unicorngmbh")};
    
   // auto upCantCopyConstruct{upMyFather}; // compile error: can't be copied. deleted function
   // auto upCantCopyAssign = upMyMother;   // compile error: can't be copied. deleted function
}