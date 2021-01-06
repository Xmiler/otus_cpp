cmake_minimum_required(VERSION 3.16.3)
project(sfinae VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
enable_testing()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sfinae main.cpp)

add_executable(tests tests.cpp)
target_include_directories(tests PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_definitions(tests PRIVATE "BOOST_TEST_DYN_LINK=1")
target_link_libraries(tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
add_test(NAME ${PROJECT_NAME} COMMAND tests)

install(TARGETS sfinae RUNTIME DESTINATION bin)
set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
