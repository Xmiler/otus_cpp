cmake_minimum_required(VERSION 3.2)

project(15_gof.4)

add_executable(observer observer.cpp)
set_target_properties(observer PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

add_executable(state state.cpp)
set_target_properties(state PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

add_executable(strategy strategy.cpp)
set_target_properties(strategy PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

add_executable(template_method template_method.cpp)
set_target_properties(template_method PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

add_executable(visitor visitor.cpp)
set_target_properties(visitor PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
