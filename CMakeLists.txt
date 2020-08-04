cmake_minimum_required(VERSION 3.0.2)
project(traj_eval)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  sensor_msgs
  std_msgs
)
# find_package(Boost REQUIRED COMPONENTS system)
# catkin_python_setup()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(vm_eval src/pose_eval.cpp)
 target_link_libraries(vm_eval
   ${catkin_LIBRARIES}
 )
