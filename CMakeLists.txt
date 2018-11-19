cmake_minimum_required(VERSION 3.3)

set(OpenCV_DIR "/home/nvidia/src/opencv/build")

project(tx2_camera)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  cv_bridge
  image_transport
  message_generation
  sensor_msgs
)

catkin_package(
  CATKIN_DEPENDS
  cv_bridge
  image_transport
  message_runtime
  sensor_msgs
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)
include_directories(include
${catkin_INCLUDE_DIRS}
${OpenCV_INCLUDE_DIRS})

find_package(OpenCV REQUIRED)

LIST(APPEND LINK_LIBS 
  ${OpenCV_LIBS}
)

add_executable(tx2_camera tx2_cameratx2_camera.cpp)
target_link_libraries(tx2_camera ${catkin_LIBRARIES})
target_link_libraries(tx2_camera ${OpenCV_LIBS})
target_link_libraries(tx2_camera ${LINK_LIBS})

















