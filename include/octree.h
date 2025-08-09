#ifndef OCTREE_H
#define OCTREE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include "vec3.h"
#include "tables.h"
#include "generation.h"
#include "functions.h"

namespace octree {

class Cell {
public:
    float x, y, z, halfsize;
    float (*generator)(float, float, float);
    bool isLeaf;
    Cell* children[8];
    Vec3 vertex;

    Cell();
    Cell(float x, float y, float z, float halfsize, float (*generator)(float, float, float));
    bool homogeneous() const;
    void split();
    void recursiveSplit(float minHalfSize);
    void printCells() const;
    void place(bool qr = false);
};

extern std::unordered_map<Vec3, Cell*> cell_id;
extern std::unordered_map<std::string, std::vector<Cell*>> cell_edge;

class Octree {
public:
    Cell* root;
    float (*generator)(float, float, float);
    Octree(float (*gen)(float, float, float));
    void print() const;
    void placeVertex();
};

} // namespace octree

#endif // OCTREE_H
