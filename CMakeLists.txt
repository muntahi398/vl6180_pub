# %Tag(FULLTEXT)%
cmake_minimum_required(VERSION 2.8.3)
project(vl6180_pub)

## Find catkin and any catkin packages   ## message_generation added
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs genmsg message_generation)

## Declare ROS messages and services
#add_message_files(FILES Num.msg)
#add_service_files(FILES AddTwoInts.srv)

## Generate added messages and services
#generate_messages(DEPENDENCIES std_msgs)

## Declare a catkin package
catkin_package()

## Build talker and listener
include_directories(include ${catkin_INCLUDE_DIRS})



add_executable(vl6180_publish src/vl6180_pub.cpp)
target_link_libraries(vl6180_publish ${catkin_LIBRARIES})
#add_dependencies(talker diagnostic_light_generate_messages_cpp)

#add_executable(diag_int_sub1 src/int_sub2.cpp)
#target_link_libraries(diag_int_sub1 ${catkin_LIBRARIES})
#add_dependencies(listener diagnostic_light_generate_messages_cpp)

# %EndTag(FULLTEXT)%
