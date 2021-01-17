// Итератор (Iterator)
#include <algorithm>
#include <iostream>
#include <vector>
#include <list>

int main() {

    std::vector<int> values{0, 1, 2, 3, 4, 5, 6, 7, 8};

    std::vector<int>::const_iterator iter1 = values.cbegin();
    ++iter1;
    // compile error - no reason to have operator<<
    // std::cout << iter1 << std::endl;
    std::cout << *iter1 << std::endl;

    std::vector<int>::iterator iter2 = values.begin() + 4;
    std::cout << *iter2 << std::endl;
    *iter2 = 10;
    std::cout << values.at(4) << std::endl;

    std::sort(values.begin(), values.end());

    std::list<int> values2 = {0, 1, 2, 3, 4, 5, 6};
    // compile error - wrong iterator
    // std::sort(values2.begin(), values2.end());

    return 0;
}