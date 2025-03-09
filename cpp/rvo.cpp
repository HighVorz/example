#include <iostream>

/*
    c++ 17 Copy Elision
        0. return A()
        1. A obj = A();  
*/

class A {
public:
    A() {
        std::cout << "default cons\n";
    }
};

A getA() {
    A a;
    return a;
}

int main() {
    A a = getA();
    return 0;
}