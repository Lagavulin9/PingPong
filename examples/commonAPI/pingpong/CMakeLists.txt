cmake_minimum_required(VERSION 3.0)
project(PingPong LANGUAGES CXX C)                         

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

### PACKAGES ###
find_package(CommonAPI REQUIRED)
find_package(CommonAPI-SomeIP REQUIRED)

# APP_INFO
set(APP_PACKAGE_NAME pingpong)
set(MAJOR_VERSION 1)
set(MINOR_VERSION 0)

include_directories(
  ./include
  ./src-gen/core
  ./src-gen/someip
  ${COMMONAPI_INCLUDE_DIRS}
  ${COMMONAPI_SOMEIP_INCLUDE_DIRS}
)

# add_executable(ping
# 	src/ping.cpp
# )
# target_link_libraries(ping CommonAPI)

add_executable(pong
	src/pong.cpp
	src/pongStubImpl.cpp
)
target_link_libraries(pong CommonAPI)