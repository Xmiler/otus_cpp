#include <iostream>
#include <iomanip>

// Did you know about inline unions?

int main() {

    union {
        unsigned long long lv;
        char * cptr;
        double dv;
    };

    // Compile error:  redeclaration of 'int iv'
    // int iv;

    std::cout << std::hex << "&iv =     " << (void*)(&lv) << std::endl;
    std::cout << std::hex << "&cptr =   " << (void*)(&cptr) << std::endl;
    std::cout << std::hex << "&dv =     " << (void*)(&dv) << std::endl;
    std::cout << std::dec << std::endl;

    lv = 0;
    dv = 3.141592654;
    std::cout << "iv = " << lv << std::endl;
    std::cout << "dv = " << dv << std::endl;
    
    return 0;
}