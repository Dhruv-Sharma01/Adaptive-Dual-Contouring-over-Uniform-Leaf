#!/bin/bash

# Script to generate all shapes using the Dual Contouring algorithm
# and create visualizations

echo "=== Dual Contouring Algorithm - Generate All Shapes ==="
echo

# Check if we're in the build directory
if [ ! -f "octree" ]; then
    echo "Error: octree executable not found!"
    echo "Please run this script from the build directory after compiling."
    echo "Build instructions:"
    echo "  mkdir build && cd build"
    echo "  cmake .."
    echo "  make"
    exit 1
fi

# Generate all shapes
echo "Generating shapes..."
echo

echo "1. Generating Sphere..."
./octree 0
echo

echo "2. Generating Torus..."
./octree 1
echo

echo "3. Generating Cube..."
./octree 2
echo

echo "4. Generating Gyroid..."
./octree 3
echo

# Check if Python environment exists
if [ ! -d "venv" ]; then
    echo "Setting up Python environment for visualization..."
    python3 -m venv venv
    source venv/bin/activate
    pip install matplotlib numpy trimesh
else
    echo "Activating existing Python environment..."
    source venv/bin/activate
fi

# Generate visualizations
echo "Generating visualizations..."
python visualize_mesh.py

echo
echo "=== Generation Complete! ==="
echo
echo "Generated files:"
echo "  - *.obj files: 3D mesh data"
echo "  - results/*.png: Visualization images"
echo
echo "To view the results:"
echo "  - Open OBJ files in any 3D modeling software (Blender, MeshLab, etc.)"
echo "  - View PNG images in any image viewer"
echo "  - Check the results/ directory for all visualizations"
