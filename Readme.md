# Adaptive-Dual-Contouring-over-Uniform-Leaf


Adaptive-Dual-Contouring-over-Uniform-Leaf is a C++ project that implements the dual contouring algorithm using an octree data structure. Dual contouring is a powerful method for extracting high-quality, crack-free isosurfaces from volumetric data, making it ideal for applications such as terrain rendering, medical imaging, and scientific visualization.

## Features

- **Dual Contouring Algorithm**: Extracts smooth isosurfaces from volumetric data using dual contouring techniques.
- **Octree-Based Spatial Partitioning**: Efficiently organizes and traverses spatial data with an octree structure.
- **Custom Vector Operations**: Includes a custom `vec3` class for 3D vector math.
- **Utility Functions**: Provides additional functionality (e.g., generation routines and lookup tables) to support the contouring process.
- **Modern C++**: Built using C++17 for improved performance and cleaner code.
- **Eigen Integration**: Uses the Eigen library for optimized linear algebra operations.

## Getting Started

### Prerequisites

- **CMake**: Version 3.10 or later.
- **C++ Compiler**: A compiler supporting C++17 (e.g., GCC, Clang, or MSVC).
- **Eigen3**: Install Eigen3 on your system. For Ubuntu, you can install it with:
  ```bash
  sudo apt-get install libeigen3-dev
  ```

### Building the Project

1. **Clone the Repository:**
   ```bash
   git clone https://github.com/Dhruv-Sharma01/Adaptive-Dual-Contouring-over-Uniform-Leaf
   cd Adaptive-Dual-Contouring-over-Uniform-Leaf/
   ```

2. **Create a Build Directory:**
   ```bash
   mkdir build && cd build
   ```

3. **Run CMake:**
   ```bash
   cmake ..
   ```

4. **Build the Project:**
   ```bash
   make
   ```

### Running the Project

After building, an executable named `octree` will be created in the `build` directory. Execute it with:
```bash
./octree
```

## Project Structure

```
Adaptive-Dual-Contouring-over-Uniform-Leaf /
└── ├── CMakeLists.txt      # CMake build configuration
    ├── include/            # Header files (e.g., vec3.h, tables.h, functions.h, octree.h)
    ├── src/                # Source files (e.g., vec3.cpp, generation.cpp, tables.cpp, functions.cpp, octree.cpp)
    └── build/              # Build directory (created during compilation)
```

## Contributing

Contributions are welcome! If you have suggestions or improvements for the dual contouring implementation, please fork the repository and submit a pull request. Make sure your changes are well-documented and tested.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Acknowledgments

- **Dual Contouring**: Appreciation for the seminal work on dual contouring which has inspired this project.
- **Eigen**: Thanks to the Eigen library developers for providing a powerful and efficient linear algebra toolkit.
