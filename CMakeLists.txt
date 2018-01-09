cmake_minimum_required(VERSION 3.1)
project(roboagents)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")

find_package (Threads)

include_directories(
  include/
)

add_executable(roboagents
  src/main.cpp
  src/robot.cpp
  src/world.cpp
)
target_link_libraries (roboagents ${CMAKE_THREAD_LIBS_INIT})


# add_executable(randtest test/rand_test.cc)

add_executable(threadtest  test/thread_test.cc)
target_link_libraries (threadtest ${CMAKE_THREAD_LIBS_INIT})

add_executable(mutextest  test/mutex_test.cc)
target_link_libraries (mutextest ${CMAKE_THREAD_LIBS_INIT})

add_executable(producertest  test/prod_cons_test.cc)
target_link_libraries (producertest ${CMAKE_THREAD_LIBS_INIT})
