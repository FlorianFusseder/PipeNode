cmake_minimum_required(VERSION 3.5)
project(bridgetest)
if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wpedantic")
endif()
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(source source.cpp)
ament_target_dependencies(source rclcpp std_msgs)

ament_package()
