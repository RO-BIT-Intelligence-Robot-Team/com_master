cmake_minimum_required(VERSION 3.0.2)
project(com_master)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  mobile_base_msgs
)
find_package(Qt5 COMPONENTS Core Gui Widgets Network)

catkin_package(

)

set (OpenCV_INClUDE_DIRS /usr/local/include /usr/local/include/opencv2)
set(OpenCV_LIB_DIR /usr/local/lib)
set(Opencv_LIBS opencv_core opencv_highgui opencv_imgcodecs opencv_videoio opencv_imgproc opencv_features2d opencv_flann opencv_calib3d)

file(GLOB_RECURSE QT_MOC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} FOLLOW_SYMLINKS include/com_master/*.h include/com_master/udp/*.h)

QT5_ADD_RESOURCES(QT_RESOURCES_CPP ${QT_RESOURCES})
QT5_WRAP_CPP(MOC_FILES include/com_master/com_master.h include/com_master/udp_transfer.h)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${Qt5Core_INCLUDE_DIRS}

)


add_executable(com_master ${MOC_FILES} src/com_master.cpp src/udp_transfer.cpp)
target_link_libraries(com_master
  ${catkin_LIBRARIES}
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
  Qt5::Network
)

add_dependencies(com_master ${catkin_EXPORTED_TARGETS})
