#include "octree.h"
#include "Eigen/Dense"
#include <limits>
#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <map>
#include <cstdlib>

using namespace std;
using namespace tables;
using functions::intersections;

// Global variable to select which shape to generate
int shape_type = 0; // 0=sphere, 1=torus, 2=cube, 3=gyroid

float myGenerator(float x, float y, float z) {
    Vec3 p(x, y, z);
    switch(shape_type) {
        case 1: return generation::torus(p);
        case 2: return generation::cube(p);
        case 3: return generation::gyroid(p);
        default: return generation::sphere(p);
    }
}

Vec3 myGradient(Vec3 p) {
    switch(shape_type) {
        case 1: return generation::torus_gradient(p);
        case 2: return generation::cube_gradient(p);
        case 3: return generation::gyroid_gradient(p);
        default: return generation::sphere_gradient(p);
    }
}

namespace octree {

unordered_map<Vec3, Cell*> cell_id;
unordered_map<string, vector<Cell*>> cell_edge;

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
                Vec3 n = myGradient(p);
                intersections_normals.push_back(make_pair(p, n));
                string key = to_string(p1.x) + "," + to_string(p1.y) + "," + to_string(p1.z) + "_" +
                            to_string(p2.x) + "," + to_string(p2.y) + "," + to_string(p2.z);
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
    } else {
        for (int i = 0; i < 8; i++) {
            if (children[i]) children[i]->place(qr);
        }
    }
}

// Octree Class
Octree::Octree(float (*gen)(float, float, float)) {
    generator = gen;
    root = new Cell(0.0, 0.0, 0.0, 2.0, generator);
    root->isLeaf = true;
    root->recursiveSplit(0.1);
}
void Octree::print() const {
    std::cout << "Root cell at (" << root->x << ", " << root->y << ", " << root->z << ") with halfsize " << root->halfsize << std::endl;
    root->printCells();
}

void Octree::placeVertex() {
    root->place();
}
} // namespace octree

void exportToOBJ(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    file << "# OBJ file generated by Dual Contouring Algorithm\n";
    file << "# Vertices\n";

    std::vector<Vec3> vertices;
    std::map<Vec3*, int> vertexMap;
    int vertexIndex = 1;

    // Collect all vertices from cells that have valid vertices
    for (auto& edge : octree::cell_edge) {
        for (auto cell : edge.second) {
            if (cell->vertex.x != -std::numeric_limits<float>::infinity()) {
                if (vertexMap.find(&cell->vertex) == vertexMap.end()) {
                    vertices.push_back(cell->vertex);
                    vertexMap[&cell->vertex] = vertexIndex++;
                    file << "v " << cell->vertex.x << " " << cell->vertex.y << " " << cell->vertex.z << "\n";
                }
            }
        }
    }

    file << "# Faces (triangles)\n";

    // Generate triangles from the triangulate function
    auto triangles = functions::triangulate();
    for (const auto& triangle : triangles) {
        if (triangle.size() >= 3) {
            file << "f";
            for (int i = 0; i < 3; i++) {
                // Find vertex index (this is a simplified approach)
                for (int j = 0; j < vertices.size(); j++) {
                    if (vertices[j].x == triangle[i].x &&
                        vertices[j].y == triangle[i].y &&
                        vertices[j].z == triangle[i].z) {
                        file << " " << (j + 1);
                        break;
                    }
                }
            }
            file << "\n";
        }
    }

    file.close();
    std::cout << "Exported mesh to " << filename << std::endl;
    std::cout << "Generated " << vertices.size() << " vertices and " << triangles.size() << " triangles." << std::endl;
}

int main(int argc, char* argv[]) {
    // Parse command line arguments
    if (argc > 1) {
        shape_type = std::atoi(argv[1]);
        if (shape_type < 0 || shape_type > 3) {
            std::cout << "Invalid shape type. Using default (sphere)." << std::endl;
            shape_type = 0;
        }
    }

    const char* shape_names[] = {"sphere", "torus", "cube", "gyroid"};
    std::cout << "Generating " << shape_names[shape_type] << " using Dual Contouring..." << std::endl;

    octree::Octree tree(myGenerator);
    std::cout << "Building octree..." << std::endl;
    tree.print();

    std::cout << "\nPlacing vertices..." << std::endl;
    tree.placeVertex();

    std::cout << "\nExporting mesh..." << std::endl;
    std::string filename = std::string(shape_names[shape_type]) + "_mesh.obj";
    exportToOBJ(filename);

    std::cout << "\nUsage: ./octree [shape_type]" << std::endl;
    std::cout << "  0 = sphere (default)" << std::endl;
    std::cout << "  1 = torus" << std::endl;
    std::cout << "  2 = cube" << std::endl;
    std::cout << "  3 = gyroid" << std::endl;

    return 0;
}
