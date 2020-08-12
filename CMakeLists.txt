cmake_minimum_required(VERSION 3.0.2)
project(traj_eval)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  sensor_msgs
  std_msgs
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

catkin_package()
add_executable(vm_eval src/vins_mono_eval.cpp)
target_link_libraries(vm_eval
   ${catkin_LIBRARIES}
)

add_executable(pose_eval src/pose_stamped.cpp)
target_link_libraries(pose_eval
   ${catkin_LIBRARIES}
)

