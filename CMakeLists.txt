cmake_minimum_required(VERSION 3.10)
project(AdaptiveDualContouring)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add include directories
include_directories(include)

# Add source files
set(SOURCES
    src/vec3.cpp
    src/generation.cpp
    src/tables.cpp
    src/functions.cpp
    src/octree.cpp
)

# Add the executable
add_executable(octree ${SOURCES})

# Enable testing
enable_testing()

# Add Google Test
add_subdirectory(/path/to/googletest ${CMAKE_BINARY_DIR}/googletest)

# Add test source files
set(TEST_SOURCES
    tests/test_octree.cpp
)

# Create test executable
add_executable(runTests ${TEST_SOURCES} ${SOURCES})

# Link test executable with Google Test libraries
target_link_libraries(runTests gtest gtest_main)

# Add tests
add_test(NAME OctreeTests COMMAND runTests)
