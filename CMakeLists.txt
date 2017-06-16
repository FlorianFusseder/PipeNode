cmake_minimum_required(VERSION 3.5)
project(semantic_segmentation)
if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Wpedantic")
endif()
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(semantic_segmentation source.cpp)
ament_target_dependencies(semantic_segmentation rclcpp std_msgs sensor_msgs)

install(TARGETS semantic_segmentation DESTINATION bin)

ament_package()
