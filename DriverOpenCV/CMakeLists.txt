project(AsynchronousGrabConsole)
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -march=native -O3 -pthread")

# OpenCV is not install in default location, if not, delete it.
set(OpenCV_DIR /opt/ros/kinetic/share/OpenCV-3.3.1-dev/)
find_package(OpenCV REQUIRED)

# set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui)

# set header file and library location
include_directories(${OpenCV_INCLUDE_DIRS} ./src /opt/Vimba2.0/VimbaCPP/Examples /opt/Vimba2.0)
link_directories("/opt/Vimba2.0/VimbaCPP/DynamicLib/x86_64bit/")
link_directories("/opt/Vimba2.0/VimbaImageTransform/DynamicLib/x86_64bit")

# print include_directory
# get_property(inc_dirs DIRECTORY PROPERTY INCLUDE_DIRECTORIES)
# message("inc_dirs = ${inc_dirs}")

# Add source directory
aux_source_directory("./src" SRC_LIST)

# Add exectuteable
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} libVimbaCPP.so libVimbaImageTransform.so)
