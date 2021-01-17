#include <any>
#include <iostream>
#include <string>

struct SomeStruct {
    int value;
};

std::ostream& operator<<(std::ostream& os, const SomeStruct& value) {
    os << "SomeStruct with value = " << value.value << std::endl;
    return os;
}

#pragma region (Usage)
struct SomeInternalStruct {
    SomeInternalStruct(const std::string& value) 
        : m_value(value) {

        }

    void doSomethingStrange() const {
        std::cout << "My value = " << m_value << std::endl;
    }
private:
    std::string m_value;
};

// target.h
void target(const std::any& value);


void source(const std::string& value) {
    auto any = std::make_any<SomeInternalStruct>(value);
    target(any);
}

// target.cpp
void target(const std::any& value) {
    const auto& casted = std::any_cast<SomeInternalStruct>(value);
    casted.doSomethingStrange();
}
#pragma endregion

int main() {

    std::any any = 10; // int
    // compile error - no operator<< for std::any
    // std::cout << any << std::endl;
    std::cout << std::any_cast<int>(any) << std::endl;
    std::cout << any.type().name() << std::endl;
    std::cout << std::endl;

    any = 2.71828f; // float
    try {
        std::cout << std::any_cast<int>(any) << std::endl;
    }
    catch(const std::bad_any_cast& ex) {
        std::cout << "int cast exception! " << ex.what() << std::endl;
    }
    try {
        std::cout << std::any_cast<double>(any) << std::endl;
    }
    catch(const std::bad_any_cast& ex) {
        std::cout << "double cast exception! " << ex.what() << std::endl;
    }
    std::cout << std::any_cast<float>(any) << std::endl;
    std::cout << any.type().name() << std::endl;
    std::cout << std::endl;

    any = "trololo"; // char []
    try {
        std::cout << std::any_cast<char*>(any) << std::endl;
    }
    catch(const std::bad_any_cast& ex) {
        std::cout << "char* cast exception! " << ex.what() << std::endl;
    }
    std::cout << std::any_cast<const char*>(any) << std::endl;
    std::cout << any.type().name() << std::endl;
    std::cout << std::endl;

    any = std::string("Hello, world!"); // std::string
    std::cout << std::any_cast<std::string>(any) << std::endl;
    std::cout << any.type().name() << std::endl;
    std::cout << std::endl;

    any = SomeStruct{42}; // SomeStruct
    std::cout << std::any_cast<SomeStruct>(any) << std::endl;
    std::cout << any.type().name() << std::endl;
    std::cout << std::endl;


    return 0;
}