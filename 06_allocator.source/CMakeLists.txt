cmake_minimum_required(VERSION 3.5)

project(06.allocator)

add_executable(logging_allocator logging_allocator.cpp)
set_target_properties(logging_allocator PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

add_executable(allocator_traits allocator_traits.cpp)
set_target_properties(allocator_traits PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED ON)

add_executable(polymorphism polymorphism.cpp)
set_target_properties(polymorphism PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)

