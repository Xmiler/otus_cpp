cmake_minimum_required(VERSION 3.16.3)
if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(ENV{TRAVIS_BUILD_NUMBER} 111)
endif()
project(sparse_matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
enable_testing()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sparse_matrix main.cpp)

add_executable(tests tests.cpp)
target_include_directories(tests PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_definitions(tests PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME ${PROJECT_NAME} COMMAND tests)

install(TARGETS sparse_matrix RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT alex.uldin@gmail.com)
include(CPack)
