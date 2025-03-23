//for linux
#include <iostream>
#include <unordered_map>
#include <iomanip>
#include "stub.h"
using namespace std;

template<class T>
void * get_ctor_addr(bool start = true)
{
	//the start vairable must be true, or the compiler will optimize out.
    if(start) goto Start;
Call_Constructor:
    //This line of code will not be executed.
	//The purpose of the code is to allow the compiler to generate the assembly code that calls the constructor.
    T();
Start:
    //The address of the line of code T() obtained by assembly

    char * p = (char*)&&Call_Constructor;//https://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html
    char* q = (char*)&&Start;

    char* x = p;

    bool find_null = false;
    int offset;
    void* ret;

    /*
        backward search
        case 1
            JUMP 2
            NOP
    */
    if (*(unsigned char*)(q-3) == 0xeb &&
        *(unsigned char*)(q-2) == 0x01 &&
        *(unsigned char*)(q-1) == 0x90 &&
        *(unsigned char*)(q-8) == 0xe8) {
        x = q - 8;
        goto FINDCALL;
    }



    /*
        forward search
        method 2 从前往后找0xe8, 要求 已经遍历到4 个 0x00
    */
    while(x < q && find_null) {
        if (*(int*)x == 0) {
            find_null = true;
        }
        x++;
    }
    while(x < q && *(unsigned char*)x != 0xe8) {
        x++;
    }

    if (x >= q || (q - x) > 8) {
        goto FAILED;
    }

FINDCALL:
    offset = *(int *)(x + 1);
    ret = x + 5 + offset;
    return ret;

FAILED:
    std::cout << "get ctor address failed, opcodes:\n";
    for(char* t = p; t < q; t++) {
        auto opcode = *(unsigned char*)(t);
        std::cout << std::setw(2)
                  << std::setfill('0')
                  << std::hex
                  << (int)opcode
                  << " ";
    }
    std::cout << "\n" << std::flush;
    return nullptr;
}

class A {
public:
    A(void* p = nullptr){cout << "I am A_constructor" << endl;}
};

class B {
public:
    B(void* p = nullptr){cout << "I am B_constructor" << endl;}
};

int main()
{
    Stub stub;
    auto xa = get_ctor_addr<A>();
    auto xb = get_ctor_addr<B>();
    std::cout << "xa: " << (void*)xa << ", xb: " << (void*)xb << "\n" << std::flush;
    stub.set(xa, xb);
    
    A aa;
    return 0;
}


