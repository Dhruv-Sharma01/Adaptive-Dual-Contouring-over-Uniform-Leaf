cmake_minimum_required(VERSION 3.10)
project(OctreeProject)

set(CMAKE_CXX_STANDARD 17)

# Include directories for header files
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find Eigen3 package and include its directories
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# List of source files
set(SOURCES
    src/vec3.cpp
    src/generation.cpp
    src/tables.cpp
    src/functions.cpp
    src/octree.cpp
)

# Create the executable target
add_executable(octree ${SOURCES})

# Link any additional libraries here if needed
