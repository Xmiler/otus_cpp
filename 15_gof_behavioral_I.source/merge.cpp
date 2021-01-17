#include <iostream>
#include <map>
#include <string>

void testMerge() {
    std::map<int, std::string> first = {
        {0, "Hellow"},
        {1, ","},
        {2, " World"},
        {3, "!"}
    };

    std::map<int, std::string> second = {
        {0, "Not a hellow"},
        {4, " "},
        {5, "Merge"},
        {6, "!"}
    };

    // The behavior is undefined if get_allocator() != source.get_allocator(). 
    second.merge(first);

    std::cout << "First after merge:" << std::endl;
    for (const auto& v : first) 
        std::cout << v.first << " <-> " << v.second << std::endl;
    std::cout << std::endl;

    std::cout << "Second after merge:" << std::endl;
    for (const auto& v : second) 
        std::cout << v.first << " <-> " << v.second << std::endl;
    std::cout << std::endl;

    std::multimap<int, std::string> multy = {
        {7, "Seven"},
        {7, "Again Seven"},
        {7, "And one more Seven"}
    };
    second.merge(multy);

    std::cout << "multy after merge:" << std::endl;
    for (const auto& v : multy) 
        std::cout << v.first << " <-> " << v.second << std::endl;
    std::cout << std::endl;

    std::cout << "Second after merge:" << std::endl;
    for (const auto& v : second) 
        std::cout << v.first << " <-> " << v.second << std::endl;
    std::cout << std::endl;

    std::multimap<int, std::string> multySecond {
        {7, "Again Seven"},
        {7, "And one more Seven"}
    };
    multySecond.merge(multy);

    std::cout << "multySecond after merge:" << std::endl;
    for (const auto& v : multySecond) 
        std::cout << v.first << " <-> " << v.second << std::endl;
    std::cout << std::endl;
}

void testExtract() {
    std::map<int, std::string> first = {
        {0, "zero"}
    };

    std::map<int, std::string>::node_type node = first.extract(0);
    std::cout << "Is extracted node empty: " << node.empty() << std::endl;

    std::map<int, std::string>::node_type emptyNode = first.extract(1);
    std::cout << "Is extracted emptyNode empty: " << emptyNode.empty() << std::endl;

    std::cout << "Is first map is empty after extraction = " << first.empty() << std::endl;

    node.key() = 1;

    std::map<int, std::string> second = {
        {0, "not zero"}
    };
    // Compile error - Node handle is a move-only type
    // auto result0 = second.insert(node);
    auto result = second.insert(std::move(node));

    for(auto& v : second) {
        std::cout << v.first << " -> " << v.second << std::endl;
    }
}

int main() {

    testMerge();

    testExtract();

    return 0;
}