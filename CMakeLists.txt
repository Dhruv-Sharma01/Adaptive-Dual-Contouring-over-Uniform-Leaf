cmake_minimum_required(VERSION 3.10)
project(AdaptiveDualContouring)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Locate Eigen3 (if needed for QEF solving later)
find_package(Eigen3 REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR} include)

# Grab all source files
file(GLOB SOURCES "src/*.cpp")

add_executable(octree ${SOURCES})
