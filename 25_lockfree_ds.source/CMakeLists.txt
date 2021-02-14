cmake_minimum_required(VERSION 3.5)
project(24_LockFree)

set(CMAKE_CXX_STANDARD 14)

add_executable(stack_1 stack_1.cpp)
set_target_properties(stack_1 PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

add_executable(stack_2 stack_2.cpp)
set_target_properties(stack_2 PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

add_executable(stack_3 stack_3.cpp)
set_target_properties(stack_3 PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

add_executable(stack_4 stack_4.cpp)
set_target_properties(stack_4 PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

add_executable(stack stack.cpp)
set_target_properties(stack PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)



find_package(Boost REQUIRED)
find_package(Threads REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_executable(boost_lock_free boost_lock_free.cpp)
set_target_properties(boost_lock_free PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)
target_link_libraries(boost_lock_free ${CMAKE_THREAD_LIBS_INIT})

add_executable(array array.cpp)
set_target_properties(array PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)
target_link_libraries(array ${CMAKE_THREAD_LIBS_INIT})