cmake_minimum_required(VERSION 3.0)
project(myApp LANGUAGES CXX C)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++14")

find_package(vsomeip3 REQUIRED)

include_directories(
  ./include
  ${VSOMEIP_INCLUDE_DIRS}
)

add_executable(myApp
  src/main.cpp
)
target_link_libraries(myApp vsomeip3)
