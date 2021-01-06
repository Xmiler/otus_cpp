#pragma once

#include <iostream>

template <typename T>
void fill_map(T &m) {
    m[0] = 1;
    for ( int i = 1; i < 10; ++i )
        m[i] = m[i-1] * i;
}

template <typename T>
void print_map(const T &m) {
    for (auto [k, v] : m) {
        std::cout << k << " " << v << std::endl;
    }
}

template <typename T>
void fill_list(T &l) {
    l.push_back(1);
    for ( int i = 1; i < 10; ++i ) {
        l.push_back(l.back()*i);
    }
}

template <typename T>
void print_list(const T &l) {
    for ( const int &el : l ) {
        std::cout << el << std::endl;
    }
}
