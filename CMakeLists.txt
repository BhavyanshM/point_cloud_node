cmake_minimum_required(VERSION 3.0.2)
project(point_cloud_node)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  pcl_conversions
  pcl_ros
  roscpp
  rospy
  sensor_msgs
  std_msgs
)

#catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES point_cloud_node
#  CATKIN_DEPENDS geometry_msgs pcl_conversions pcl_ros roscpp rospy sensor_msgs std_msgs
#  DEPENDS system_lib
#)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} src/PointCloudProcessor.cpp)
 target_link_libraries(${PROJECT_NAME}
   ${catkin_LIBRARIES}
 )


