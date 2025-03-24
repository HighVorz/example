#include <iostream>

class Base {
    virtual void f() {}
};

class _Base {
    virtual void f() {}
    virtual void h() {}
};

class BaseOne {
public:
    virtual void f() {}
    int m_baseone;
    /*
        8 byte:  vtable
        4 byte:  m_baseone + 4 byte: random
    */
};

class BaseTwo {
public:
    virtual void f() {}
    int m_basetwo;
    /*
        8 byte:  vtable
        4 byte:  m_basetwo + 4 byte: random
    */
};

class BaseThree {
public:
    virtual void f() {}
    int m_basethree;
    /*
        8 byte:  vtable
        4 byte:  m_basethree + 4 byte: random
    */
};

class Derive : public BaseOne, public BaseTwo, public BaseThree {
    virtual void f() {}
public:
    int m_derive;
    /*
        8 byte:  vtable
        4 byte:  m_baseone + 4 byte: random
        8 byte:  vtable
        4 byte:  m_basetwo + 4 byte: random
        8 byte:  vtable
        4 byte:  m_baseone + 4 byte: m_derive
    */
};

int main() {
    Derive d;
    BaseOne bone;
    Base b;
    _Base _b;

    std::cout << "Derive size: " << sizeof(d) << "\n";
    std::cout << "BaseOne size: " << sizeof(bone) << "\n";
    std::cout << "Base size: " << sizeof(b) << "\n";
    std::cout << "_Base size: " << sizeof(_b) << "\n";
    /*
        Derive size:  48
        BaseOne size: 16
        Base size:    8
        _Base size:   8
    */

    std::cout << "Derive ptr: " << (void*)&d << "\n";
    std::cout << "BaseOne ptr: " << (void*)(BaseOne*)&d << "\n";
    std::cout << "BaseTwo ptr: " << (void*)(BaseTwo*)&d << "\n";
    std::cout << "BaseThree ptr: " << (void*)(BaseThree*)&d << "\n";
    std::cout << "Derive::m_derive ptr: " << (void*)(BaseThree*)&(d.m_derive) << "\n";

    /*
        Derive ptr:             0x7ffc6682ae60
        BaseOne ptr:            0x7ffc6682ae60
        BaseTwo ptr:            0x7ffc6682ae70
        BaseThree ptr:          0x7ffc6682ae80
        Derive::m_derive ptr:   0x7ffc6682ae8c
    */


    return 0;
}