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

set(INTERFACE "someip/v${MAJOR_VERSION}/${APP_PACKAGE_NAME}")
add_library(PongStub SHARED
  src-gen/${INTERFACE}/PongSomeIPDeployment.cpp
  src-gen/${INTERFACE}/PongSomeIPStubAdapter.cpp
)
target_link_libraries(PongStub CommonAPI-SomeIP)

add_library(PongProxy SHARED
  src-gen/${INTERFACE}/PongSomeIPProxy.cpp
)
target_link_libraries(PongProxy CommonAPI-SomeIP)