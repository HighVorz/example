#include <iostream>

/*
    The object must be initialized, so one and only one constructor will be called
*/

class A {
public:
    A() = default;

    A(const A& obj) {
        std::cout << "copy cons\n";
    }

    A& operator=(const A& obj) {
        std::cout << "assign override\n";
    } 
};

int main() {
    A a;
    A b = a;    // initialize will choose copy cons func, same as A b(a)
    b = a;      // assign will choose assign override func 
    
    return 0;
}