# roscpp_tutorials
A repository with all the package descriptions and packages and source code to learn roscpp

Initialize a workspace:

```
mkdir -p catkin_ws/src
cd catkin_ws/src
catkin_create_pkg intro_nodes std_msgs roscpp 
```

Now we write the source code in the /src directory of intro_nodes
Add the following lines to the CMakeLists.txt file
```
add_executable(publisher src/publisher.cpp)
add_executable(subscriber src/subscriber.cpp)
target_link_libraries(publisher ${catkin_LIBRARIES})
target_link_libraries(subscriber ${catkin_LIBRARIES})
```
To run the nodes go to the root of your workspace
```
roscore
rosrun intro_nodes publisher
rosrun intro_nodes subscriber
```
