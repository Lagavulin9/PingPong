cmake_minimum_required(VERSION 3.0)
project(pingpong LANGUAGES CXX C)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -std=c++14")

find_package(vsomeip3 REQUIRED)

set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)

include_directories(
  ./include
  ${VSOMEIP_INCLUDE_DIRS}
)

add_executable(ping
  src/ping.cpp
)
target_link_libraries(ping vsomeip3)

add_executable(pong
  src/pong.cpp
)
target_link_libraries(pong vsomeip3)