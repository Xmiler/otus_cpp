cmake_minimum_required(VERSION 3.5)
project(multithreading)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)
find_package(Threads)

add_executable(raceconditions raceconditions.cpp)
target_link_libraries(raceconditions
  ${CMAKE_THREAD_LIBS_INIT}
  )

add_executable(thread thread.cpp)
target_link_libraries(thread
  ${CMAKE_THREAD_LIBS_INIT}
  )

add_executable(promise promise.cpp)
target_link_libraries(promise
  ${CMAKE_THREAD_LIBS_INIT}
  )

add_executable(async async.cpp)
target_link_libraries(async
  ${CMAKE_THREAD_LIBS_INIT}
  )

add_executable(condition condition.cpp)
target_link_libraries(condition
  ${CMAKE_THREAD_LIBS_INIT}
  )

