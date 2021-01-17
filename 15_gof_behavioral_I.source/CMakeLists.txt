cmake_minimum_required(VERSION 3.3)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.10" CACHE STRING "Minimum OS X deployment version")

project(gof_3)

add_executable(command command.cpp)
set_target_properties(command PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )


add_executable(chain_of_responsibility chain_of_responsibility.cpp)
set_target_properties(chain_of_responsibility PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(interpreter interpreter.cpp)
set_target_properties(interpreter PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(iterator iterator.cpp)
set_target_properties(iterator PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(mediator mediator.cpp)
set_target_properties(mediator PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(memento memento.cpp)
set_target_properties(memento PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        )

add_executable(merge merge.cpp)
set_target_properties(merge PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )
