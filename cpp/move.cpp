#include <iostream>
#include <vector>

class A {
public:
    A() {
        std::cout << "default cons\n";
    }

    A(const A& obj) {
        std::cout << "copy cons\n";
    }

    A(A&& obj) {
        std::cout << "move cons\n";
    }
};

A getA() {
    A a;
    return a;
}

int main() {
    A a;
    A b = std::move(a);
    // A&& c = a; error
    A&& c = std::move(a);

    A&& d = getA();
    return 0;
}