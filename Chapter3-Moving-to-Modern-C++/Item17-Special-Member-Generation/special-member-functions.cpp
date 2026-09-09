#include <iostream>
#include <vector>
/*
Special member functions are 
constructor, destructor
copy constructor, copy assignment
move constructor, move assignment -- Added in C++11
*/

using namespace std;

/*
    We are going to use vector<int> as our member data type.
    Primitives can't be used since copy and move is the same thing for them.
*/

class allDefaults{
    public: 
    vector<int> data;
    friend ostream& operator<<(ostream& os, const allDefaults& a){
        os << (a.data.size() > 0 ? "[" : "[]");
        for(size_t i = 0; i < a.data.size();i++){
            os << a.data[i] << (i == a.data.size() - 1? "]": ", ");;
        }
        return os;
    }
};

// when only 1 move operation is defined, the other one is deleted.
// This is not demonstrated here.

class onlyMoves{
    public:
    vector<int> data;
    onlyMoves(vector<int> data_):data{std::move(data_)}{}

    onlyMoves(onlyMoves&& toBeMoved):data{std::move(toBeMoved.data)}{}

    onlyMoves& operator=(onlyMoves&& toBeMoved){
        if (this == &toBeMoved) return *this;
        data = std::move(toBeMoved.data);
        return *this;
    }
    friend ostream& operator<<(ostream& os, const onlyMoves& a){
        os << (a.data.size() > 0 ? "[" : "[]");
        for(size_t i = 0; i < a.data.size();i++){
            os << a.data[i] << (i == a.data.size() - 1? "]": ", ");;
        }
        return os;
    }
};

class onlyCopies{
    public:
    vector<int> data;
    onlyCopies(vector<int> data_):data{std::move(data_)}{}
    onlyCopies& operator=(const onlyCopies& toBeCopied){
        auto& data_ = toBeCopied.data;
        data.resize(data_.size());
        for(size_t i = 0; i < data_.size(); i++){
            data[i] = data_[i];
        }
        return *this;
    }
    onlyCopies(const onlyCopies& toBeCopied):data(toBeCopied.data.size(),0){
        auto& data_ = toBeCopied.data;
        for(size_t i = 0; i < data_.size(); i++){
            data[i] = data_[i];
        }
    }
    friend ostream& operator<<(ostream& os, const onlyCopies& a){
            os << (a.data.size() > 0 ? "[" : "[]");
            for(size_t i = 0; i < a.data.size();i++){
                os << a.data[i] << (i == a.data.size() - 1? "]": ", ");;
            }
            return os;
    }
};

class onlyConstructor{
    public:
    vector<int>data;
    onlyConstructor():data(10,5){}
    friend ostream& operator<<(ostream& os, const onlyConstructor& a){
            os << (a.data.size() > 0 ? "[" : "[]");
            for(size_t i = 0; i < a.data.size();i++){
                os << a.data[i] << (i == a.data.size() - 1? "]": ", ");;
            }
            return os;
    }
};

// Suppresses move operations.
// Copies should also be suppressed by principle but C++98 allowed copy operations
// when destructor was defined. Backwards compatibility requires continued support for this.
class onlyDestructor{
    public:
    vector<int> data;
    ~onlyDestructor() noexcept {
        cout << "Destructing onlyDefaultDestructor!!" << endl;
    }
    friend ostream& operator<<(ostream& os, const onlyDestructor& a){
            os << (a.data.size() > 0 ? "[" : "[]");
            for(size_t i = 0; i < a.data.size();i++){
                os << a.data[i] << (i == a.data.size() - 1? "]": ", ");;
            }
            return os;
    }
};

int main(){
    //  ====================== all Defaults =================================
    allDefaults constructor{};
    allDefaults copyConstructor{constructor};
    allDefaults copied{vector<int>{1,2,3}};
    allDefaults copyAssignment;
    cout << "Copy assignment before: " << copyAssignment << endl; // default constructor of int assigns 0;
    copyAssignment = copied;
    cout << "Copy assignment after: " << copyAssignment << endl; // default constructor of int assigns 0;
    allDefaults moveConstructor{allDefaults{vector<int>{5}}};
    cout << "Move Constructor: " << moveConstructor << endl;
    allDefaults moveConstructor2{std::move(copied)};
    cout << "Move Constructor2: " << moveConstructor2 << " Copied after being moved: " << copied << endl;
    allDefaults moveAssignment{};
    moveAssignment = std::move(moveConstructor2);
    cout << "Move Assignment: " << moveAssignment << " Leftover of Move Assignment: " << moveConstructor2 << endl;
    

    //  ====================== only Copies =================================
    //onlyCopies defaultConstructor; // compile error: no default constructor exists.
    onlyCopies toBeCopied{vector<int>{1,2,3}};
    cout << "Only Copies toBeCopied: " << toBeCopied << endl;
    onlyCopies copyConstructorOC{toBeCopied};
    cout << "Only Copies copyConstructor: " <<copyConstructorOC << " Only Copies toBeCopied: " << toBeCopied << endl;
    onlyCopies copyAssignmentOC{vector<int>{5,6,7}};
    copyConstructorOC = copyAssignmentOC;
    cout << "Only Copies copyConstructor after copyAssignment: " << copyConstructorOC << " Only Copies copyAssignment: " << copyAssignmentOC << endl;
    // Uses copy assignment!!
    copyAssignmentOC = std::move(toBeCopied);
    cout << "Only Copies copyAssignment after moving : " << copyAssignmentOC << " Only Copies toBeCopied: " << toBeCopied << endl;
    // uses copy constructor!!
    onlyCopies moveConstructorOC{std::move(toBeCopied)};
    cout << "Only Copies moveConstructor after moving : " << moveConstructorOC << " Only Copies toBeCopied: " << toBeCopied << endl;
    
    
    // ======================== only Moves =================================
    onlyMoves toBeMoved{vector<int>{1,2,3}};
    cout << "onlyMoves toBeMoved: " << toBeMoved << endl;
    // default copy constructor is implicitly declared as deleted because ‘onlyMoves’ declares a move constructor or move assignment operator
    //onlyMoves copyConstructorOM{toBeMoved};

    // default copy assignment is implicitly declared as deleted because ‘onlyMoves’ declares a move constructor or move assignment operator
    //onlyMoves copyAssignmentOM{vector<int>{5,6,7}};
    //copyAssignmentOM = toBeMoved;

    onlyMoves moveConstructorOM{std::move(toBeMoved)};
    cout << "onlyMoves moveConstructorOM: " << moveConstructorOM <<" onlyMoves leftover of moveConstructor: " << toBeMoved  << endl;
    onlyMoves moveAssignmentOM{vector<int>{7,8,9}};
    cout << "onlyMoves moveAssignment before :" << moveAssignmentOM << " moveAssignment argument: "<< moveConstructorOM << endl;
    moveAssignmentOM = std::move(moveConstructorOM);
    cout << "onlyMoves moveAssignmentOM after :" << moveAssignmentOM << " moveAssignment leftover: "<< moveConstructorOM << endl;
    

    // ========================= only Default Constructor ============================
    // Default constructor doesn't suppress anything.
    onlyConstructor defaultConstructorOCons;
    cout << "only Constructor: " << defaultConstructorOCons << endl;
    defaultConstructorOCons.data[1] = 2;
    onlyConstructor copyConstructorOCcons{defaultConstructorOCons};
    cout << "only Constructor copyConstructor: " << copyConstructorOCcons << endl;
    onlyConstructor copyAssignmentOCons;
    copyAssignmentOCons = defaultConstructorOCons;
    cout << "only Constructor copy assignment: " << copyAssignmentOCons << endl;
    onlyConstructor moveConstructorOCons{std::move(defaultConstructorOCons)};
    cout << "only Constructor move constructor: " << moveConstructorOCons << " move constructor leftover: " << defaultConstructorOCons << endl;
    onlyConstructor moveAssignmentOCons; 
    moveAssignmentOCons = std::move(moveConstructorOCons);
    cout << "only Constructor move assignment: " << moveAssignmentOCons << " move assignment leftover: " << moveConstructorOCons << endl;
    

    // ========================== only Default Destructor ==============================
    onlyDestructor defaultConstructorOD;// Default constructor is there!
    cout << "only Destructor default constructor: " << defaultConstructorOD << endl;
    defaultConstructorOD.data.push_back(2);
    onlyDestructor copyConstructorOD{defaultConstructorOD};// default copy constructor is there!
    cout << "only Destructor default copy constructor: " << copyConstructorOD << endl;
    onlyDestructor copyAssignmentOD;
    copyAssignmentOD = defaultConstructorOD;
    cout << "only Destructor default copy assignment: " << copyAssignmentOD << endl;
    // Uses copy constructor!
    onlyDestructor moveConstructorOD{std::move(defaultConstructorOD)};
    cout << "only Destructor default move constructor: " << moveConstructorOD << " moveConstructor leftover: " << defaultConstructorOD<<  endl;
    // Uses copy Assignment!
    onlyDestructor moveAssignmentOD;
    moveAssignmentOD = std::move(moveConstructorOD);
    cout << "only Destructor default move assignment: " << moveAssignmentOD << " move assignment leftover: " << moveConstructorOD<<  endl;
}
