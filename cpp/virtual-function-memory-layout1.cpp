#include <iostream>

class BaseOne {
    virtual void f() {}
};

class BaseTwo {
    virtual void f() {}
};

class BaseThree {
    virtual void f() {}
};

class Derive : BaseOne, BaseTwo, BaseThree {
    virtual void f() {}
};

int main() {
    Derive d;
    std::cout << "Derive ptr: " << (void*)&d << "\n";
    std::cout << "BaseOne ptr: " << (void*)(BaseOne*)&d << "\n";
    std::cout << "BaseTwo ptr: " << (void*)(BaseTwo*)&d << "\n";
    std::cout << "BaseThree ptr: " << (void*)(BaseThree*)&d << "\n";

    /*
        Derive ptr:     0x7fffc6a661a0
        BaseOne ptr:    0x7fffc6a661a0
        BaseTwo ptr:    0x7fffc6a661a8
        BaseThree ptr:  0x7fffc6a661b0
    */

    return 0;
}