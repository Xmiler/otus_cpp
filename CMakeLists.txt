cmake_minimum_required(VERSION 3.2)
project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ip_filter_cli main.cpp)
