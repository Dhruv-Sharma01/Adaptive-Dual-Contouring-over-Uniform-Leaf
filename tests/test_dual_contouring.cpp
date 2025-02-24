#include <gtest/gtest.h>
#include "octree.h"  // Adjust the path as necessary

// Test case for the Octree class
TEST(OctreeTest, Initialization) {
    // Create an instance of the Octree
    Octree octree;

    // Perform initialization tests
    EXPECT_EQ(octree.getNodeCount(), 0);
    EXPECT_TRUE(octree.isEmpty());
}

// Additional test cases...
