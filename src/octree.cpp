#include "octree.h"
#include "Eigen/Dense"
#include <limits>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;
using namespace octree;
using namespace tables;
using myGenerator = generation::sphere;
using functions::intersections;
using generation::sphere_gradient;

unordered_map<Vec3, Cell*> cell_id;
unordered_map<vector<Vec3>, vector<Cell*>> cell_edge;

Cell::Cell() : x(0), y(0), z(0), halfsize(0), generator(nullptr), isLeaf(false),
    vertex(Vec3(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity())) {
    for (int i = 0; i < 8; i++) {
        children[i] = nullptr;
    }
}

Cell::Cell(float x, float y, float z, float halfsize, float (*generator)(float, float, float))
    : x(x), y(y), z(z), halfsize(halfsize), generator(generator), isLeaf(true), vertex(Vec3(0,0,0)) {
    for (int i = 0; i < 8; i++) {
        children[i] = nullptr;
    }
    cell_id[Vec3(x, y, z)] = this;
}

bool Cell::homogeneous() const {
    if (!generator) return false;
    float centerVal = generator(x, y, z);
    int total = 1;
    for (int i = 0; i < 8; i++) {
        float nx = (i & 1) ? x - halfsize : x + halfsize;
        float ny = (i & 2) ? y - halfsize : y + halfsize;
        float nz = (i & 4) ? z - halfsize : z + halfsize;
        if (generator(nx, ny, nz) * centerVal > 0) total++;
    }
    return (total == 9);
}

void Cell::split() {
    isLeaf = false;
    for (int i = 0; i < 8; i++) {
        float newX = (i & 1) ? x + halfsize / 2 : x - halfsize / 2;
        float newY = (i & 2) ? y + halfsize / 2 : y - halfsize / 2;
        float newZ = (i & 4) ? z + halfsize / 2 : z - halfsize / 2;
        children[i] = new Cell(newX, newY, newZ, halfsize / 2, generator);
        children[i]->isLeaf = true;
    }
}

void Cell::recursiveSplit(float minHalfSize) {
    if (halfsize <= minHalfSize || homogeneous()) return;
    split();
    for (int i = 0; i < 8; i++) {
        if (children[i]) children[i]->recursiveSplit(minHalfSize);
    }
}

void Cell::printCells() const {
    for (int i = 0; i < 8; i++) {
        if (children[i]) {
            cout << "Cell at (" << children[i]->x << ", " << children[i]->y << ", " << children[i]->z
                 << ") with halfsize " << children[i]->halfsize << endl;
            children[i]->printCells();
        }
    }
}

void Cell::place(bool qr) {
    if (isLeaf && !homogeneous()) {
        vector<Vec3> vertices = { Vec3(x - halfsize, y - halfsize, z - halfsize),
                                  Vec3(x - halfsize, y - halfsize, z + halfsize),
                                  Vec3(x - halfsize, y + halfsize, z - halfsize),
                                  Vec3(x - halfsize, y + halfsize, z + halfsize),
                                  Vec3(x + halfsize, y - halfsize, z - halfsize),
                                  Vec3(x + halfsize, y - halfsize, z + halfsize),
                                  Vec3(x + halfsize, y + halfsize, z - halfsize),
                                  Vec3(x + halfsize, y + halfsize, z + halfsize) };
        vector<pair<Vec3, Vec3>> intersections_normals;
        for (auto j : edgeTable) {
            Vec3 p1 = vertices[j[0]];
            Vec3 p2 = vertices[j[1]];
            float v1 = generator(p1.x, p1.y, p1.z);
            float v2 = generator(p2.x, p2.y, p2.z);
            if (v1 * v2 < 0) {
                Vec3 p = intersections(p1, p2, v1, v2);
                Vec3 n = sphere_gradient(p);
                intersections_normals.push_back(make_pair(p, n));
                vector<Vec3> key = { p1, p2 };
                cell_edge[key].push_back(this);
            }
        }
        if (!qr) { qr = true; } // default to SVD branch
        if (qr) {
            int m = intersections_normals.size();
            if (m == 0) return;
            Eigen::MatrixXf A_mat(m, 3);
            Eigen::VectorXf d_vec(m);
            for (int i = 0; i < m; i++) {
                Vec3 n = intersections_normals[i].second;
                Vec3 p = intersections_normals[i].first;
                A_mat(i, 0) = n.x;
                A_mat(i, 1) = n.y;
                A_mat(i, 2) = n.z;
                d_vec(i) = n.x * p.x + n.y * p.y + n.z * p.z;
            }
            Eigen::Vector3f x_vec = A_mat.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(d_vec);
            vertex = Vec3(x_vec(0), x_vec(1), x_vec(2));
        }
    } else {\n        for (int i = 0; i < 8; i++) {\n            if (children[i]) children[i]->place(qr);\n        }\n    }\n}\n\n// Octree Class\nOctree::Octree(float (*gen)(float, float, float)) {\n    generator = gen;\n    root = new Cell(0.0, 0.0, 0.0, 2.0, generator);\n    root->isLeaf = true;\n    root->recursiveSplit(0.1);\n}\n\nvoid Octree::print() const {\n    std::cout << \"Root cell at (\" << root->x << \", \" << root->y << \", \" << root->z << \") with halfsize \" << root->halfsize << std::endl;\n    root->printCells();\n}\n\nvoid Octree::placeVertex() {\n    root->place();\n}\n\n} // namespace octree\n\nint main() {\n    octree::Octree tree(myGenerator);\n    tree.print();\n    tree.placeVertex();\n    return 0;\n}\nEOF

echo "Created src/octree.cpp"

###############################
# Create source: src/main.cpp
###############################
cat << 'EOF' > "$PROJECT_ROOT/src/main.cpp"
#include <iostream>
#include "octree.h"
#include "generation.h"

using namespace std;
using namespace octree;
using myGenerator = generation::sphere;

int main() {
    // Create the octree using the sphere function as the generator
    Octree tree(myGenerator);
    tree.print();
    tree.placeVertex();
    return 0;
}
