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

add_executable(loop_closed_eval src/loop_closure.cpp)
target_link_libraries(loop_closed_eval
   ${catkin_LIBRARIES}
)

add_executable(rovio_eval src/rovio_eval.cpp)
target_link_libraries(rovio_eval
   ${catkin_LIBRARIES}
)

add_executable(okvis_eval src/okvis_eval.cpp)
target_link_libraries(okvis_eval
   ${catkin_LIBRARIES}
)

add_executable(kimera_eval src/kimera_eval.cpp)
target_link_libraries(kimera_eval
   ${catkin_LIBRARIES}
)

add_executable(msckf_eval src/msckf_eval.cpp)
target_link_libraries(msckf_eval
   ${catkin_LIBRARIES}
)

add_executable(svo_eval src/svo_eval.cpp)
target_link_libraries(svo_eval
   ${catkin_LIBRARIES}
)