cmake_minimum_required(VERSION 3.2)
project(ips_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(lib)

add_executable(ips_filter_cli main.cpp)
target_link_libraries(ips_filter_cli PRIVATE ips_filter)
