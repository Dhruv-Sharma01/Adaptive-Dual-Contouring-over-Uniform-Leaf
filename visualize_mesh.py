#!/usr/bin/env python3
"""
Visualization script for the Dual Contouring algorithm results.
This script loads the generated OBJ mesh file and creates various visualizations.
"""

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import trimesh
import os

def load_obj_file(filename):
    """Load vertices and faces from an OBJ file."""
    vertices = []
    faces = []
    
    with open(filename, 'r') as file:
        for line in file:
            line = line.strip()
            if line.startswith('v '):
                # Vertex line: v x y z
                parts = line.split()
                vertex = [float(parts[1]), float(parts[2]), float(parts[3])]
                vertices.append(vertex)
            elif line.startswith('f '):
                # Face line: f v1 v2 v3 (1-indexed)
                parts = line.split()
                face = [int(parts[1])-1, int(parts[2])-1, int(parts[3])-1]  # Convert to 0-indexed
                faces.append(face)
    
    return np.array(vertices), np.array(faces)

def create_wireframe_plot(vertices, faces, title="Dual Contouring Wireframe"):
    """Create a wireframe visualization of the mesh."""
    fig = plt.figure(figsize=(12, 10))
    ax = fig.add_subplot(111, projection='3d')
    
    # Plot vertices
    ax.scatter(vertices[:, 0], vertices[:, 1], vertices[:, 2], 
               c='red', s=1, alpha=0.6, label='Vertices')
    
    # Plot edges
    for face in faces:
        # Draw the three edges of each triangle
        for i in range(3):
            start = vertices[face[i]]
            end = vertices[face[(i+1)%3]]
            ax.plot([start[0], end[0]], [start[1], end[1]], [start[2], end[2]], 
                   'b-', alpha=0.3, linewidth=0.5)
    
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.set_title(title)
    ax.legend()
    
    # Set equal aspect ratio
    max_range = np.array([vertices[:,0].max()-vertices[:,0].min(),
                         vertices[:,1].max()-vertices[:,1].min(),
                         vertices[:,2].max()-vertices[:,2].min()]).max() / 2.0
    mid_x = (vertices[:,0].max()+vertices[:,0].min()) * 0.5
    mid_y = (vertices[:,1].max()+vertices[:,1].min()) * 0.5
    mid_z = (vertices[:,2].max()+vertices[:,2].min()) * 0.5
    ax.set_xlim(mid_x - max_range, mid_x + max_range)
    ax.set_ylim(mid_y - max_range, mid_y + max_range)
    ax.set_zlim(mid_z - max_range, mid_z + max_range)
    
    return fig

def create_surface_plot(vertices, faces, title="Dual Contouring Surface"):
    """Create a surface visualization of the mesh."""
    fig = plt.figure(figsize=(12, 10))
    ax = fig.add_subplot(111, projection='3d')
    
    # Create triangular surface plot
    ax.plot_trisurf(vertices[:, 0], vertices[:, 1], vertices[:, 2], 
                    triangles=faces, alpha=0.8, cmap='viridis', 
                    linewidth=0.1, edgecolor='black')
    
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')
    ax.set_title(title)
    
    # Set equal aspect ratio
    max_range = np.array([vertices[:,0].max()-vertices[:,0].min(),
                         vertices[:,1].max()-vertices[:,1].min(),
                         vertices[:,2].max()-vertices[:,2].min()]).max() / 2.0
    mid_x = (vertices[:,0].max()+vertices[:,0].min()) * 0.5
    mid_y = (vertices[:,1].max()+vertices[:,1].min()) * 0.5
    mid_z = (vertices[:,2].max()+vertices[:,2].min()) * 0.5
    ax.set_xlim(mid_x - max_range, mid_x + max_range)
    ax.set_ylim(mid_y - max_range, mid_y + max_range)
    ax.set_zlim(mid_z - max_range, mid_z + max_range)
    
    return fig

def create_multiple_views(vertices, faces):
    """Create multiple views of the mesh in a single figure."""
    fig = plt.figure(figsize=(16, 12))
    
    # Calculate bounds for consistent scaling
    max_range = np.array([vertices[:,0].max()-vertices[:,0].min(),
                         vertices[:,1].max()-vertices[:,1].min(),
                         vertices[:,2].max()-vertices[:,2].min()]).max() / 2.0
    mid_x = (vertices[:,0].max()+vertices[:,0].min()) * 0.5
    mid_y = (vertices[:,1].max()+vertices[:,1].min()) * 0.5
    mid_z = (vertices[:,2].max()+vertices[:,2].min()) * 0.5
    
    # View 1: Isometric view
    ax1 = fig.add_subplot(221, projection='3d')
    ax1.plot_trisurf(vertices[:, 0], vertices[:, 1], vertices[:, 2], 
                     triangles=faces, alpha=0.8, cmap='viridis')
    ax1.set_title('Isometric View')
    ax1.set_xlim(mid_x - max_range, mid_x + max_range)
    ax1.set_ylim(mid_y - max_range, mid_y + max_range)
    ax1.set_zlim(mid_z - max_range, mid_z + max_range)
    ax1.view_init(elev=30, azim=45)
    
    # View 2: Front view (XZ plane)
    ax2 = fig.add_subplot(222, projection='3d')
    ax2.plot_trisurf(vertices[:, 0], vertices[:, 1], vertices[:, 2], 
                     triangles=faces, alpha=0.8, cmap='plasma')
    ax2.set_title('Front View')
    ax2.set_xlim(mid_x - max_range, mid_x + max_range)
    ax2.set_ylim(mid_y - max_range, mid_y + max_range)
    ax2.set_zlim(mid_z - max_range, mid_z + max_range)
    ax2.view_init(elev=0, azim=0)
    
    # View 3: Side view (YZ plane)
    ax3 = fig.add_subplot(223, projection='3d')
    ax3.plot_trisurf(vertices[:, 0], vertices[:, 1], vertices[:, 2], 
                     triangles=faces, alpha=0.8, cmap='coolwarm')
    ax3.set_title('Side View')
    ax3.set_xlim(mid_x - max_range, mid_x + max_range)
    ax3.set_ylim(mid_y - max_range, mid_y + max_range)
    ax3.set_zlim(mid_z - max_range, mid_z + max_range)
    ax3.view_init(elev=0, azim=90)
    
    # View 4: Top view (XY plane)
    ax4 = fig.add_subplot(224, projection='3d')
    ax4.plot_trisurf(vertices[:, 0], vertices[:, 1], vertices[:, 2], 
                     triangles=faces, alpha=0.8, cmap='inferno')
    ax4.set_title('Top View')
    ax4.set_xlim(mid_x - max_range, mid_x + max_range)
    ax4.set_ylim(mid_y - max_range, mid_y + max_range)
    ax4.set_zlim(mid_z - max_range, mid_z + max_range)
    ax4.view_init(elev=90, azim=0)
    
    plt.tight_layout()
    return fig

def print_mesh_statistics(vertices, faces):
    """Print statistics about the mesh."""
    print(f"\n=== Mesh Statistics ===")
    print(f"Number of vertices: {len(vertices)}")
    print(f"Number of faces: {len(faces)}")
    print(f"Vertex bounds:")
    print(f"  X: [{vertices[:, 0].min():.3f}, {vertices[:, 0].max():.3f}]")
    print(f"  Y: [{vertices[:, 1].min():.3f}, {vertices[:, 1].max():.3f}]")
    print(f"  Z: [{vertices[:, 2].min():.3f}, {vertices[:, 2].max():.3f}]")
    
    # Calculate mesh center and size
    center = vertices.mean(axis=0)
    size = vertices.max(axis=0) - vertices.min(axis=0)
    print(f"Mesh center: ({center[0]:.3f}, {center[1]:.3f}, {center[2]:.3f})")
    print(f"Mesh size: ({size[0]:.3f}, {size[1]:.3f}, {size[2]:.3f})")

def visualize_all_shapes():
    """Visualize all generated shapes."""
    shapes = [
        ("sphere_mesh.obj", "Sphere"),
        ("cube_mesh.obj", "Cube"),
        ("gyroid_mesh.obj", "Gyroid")
    ]

    # Create output directory for images
    output_dir = "results"
    os.makedirs(output_dir, exist_ok=True)

    # Create a comprehensive comparison figure
    fig = plt.figure(figsize=(20, 15))

    valid_shapes = []
    for i, (obj_file, shape_name) in enumerate(shapes):
        if os.path.exists(obj_file):
            print(f"Loading {shape_name} from {obj_file}...")
            vertices, faces = load_obj_file(obj_file)
            print_mesh_statistics(vertices, faces)
            valid_shapes.append((vertices, faces, shape_name))

            # Create individual visualizations
            print(f"Creating {shape_name.lower()} visualizations...")

            # Surface plot
            fig_surf = create_surface_plot(vertices, faces, f"Dual Contouring - {shape_name}")
            fig_surf.savefig(f"{output_dir}/{shape_name.lower()}_surface.png", dpi=300, bbox_inches='tight')
            plt.close(fig_surf)

            # Multiple views
            fig_multi = create_multiple_views(vertices, faces)
            fig_multi.suptitle(f"Dual Contouring - {shape_name} (Multiple Views)", fontsize=16)
            fig_multi.savefig(f"{output_dir}/{shape_name.lower()}_multiple_views.png", dpi=300, bbox_inches='tight')
            plt.close(fig_multi)
        else:
            print(f"Warning: {obj_file} not found, skipping {shape_name}")

    # Create comparison figure
    if valid_shapes:
        fig, axes = plt.subplots(2, len(valid_shapes), figsize=(6*len(valid_shapes), 12),
                                subplot_kw={'projection': '3d'})
        if len(valid_shapes) == 1:
            axes = axes.reshape(2, 1)

        for i, (vertices, faces, shape_name) in enumerate(valid_shapes):
            # Surface view
            ax1 = axes[0, i]
            ax1.plot_trisurf(vertices[:, 0], vertices[:, 1], vertices[:, 2],
                           triangles=faces, alpha=0.8, cmap='viridis')
            ax1.set_title(f'{shape_name} - Surface')
            ax1.view_init(elev=30, azim=45)

            # Set equal aspect ratio
            max_range = np.array([vertices[:,0].max()-vertices[:,0].min(),
                                vertices[:,1].max()-vertices[:,1].min(),
                                vertices[:,2].max()-vertices[:,2].min()]).max() / 2.0
            mid_x = (vertices[:,0].max()+vertices[:,0].min()) * 0.5
            mid_y = (vertices[:,1].max()+vertices[:,1].min()) * 0.5
            mid_z = (vertices[:,2].max()+vertices[:,2].min()) * 0.5
            ax1.set_xlim(mid_x - max_range, mid_x + max_range)
            ax1.set_ylim(mid_y - max_range, mid_y + max_range)
            ax1.set_zlim(mid_z - max_range, mid_z + max_range)

            # Wireframe view
            ax2 = axes[1, i]
            ax2.scatter(vertices[:, 0], vertices[:, 1], vertices[:, 2],
                       c='red', s=0.5, alpha=0.6)

            # Plot edges (sample for performance)
            edge_sample = min(len(faces), 500)  # Limit edges for performance
            for face in faces[:edge_sample]:
                for j in range(3):
                    start = vertices[face[j]]
                    end = vertices[face[(j+1)%3]]
                    ax2.plot([start[0], end[0]], [start[1], end[1]], [start[2], end[2]],
                           'b-', alpha=0.3, linewidth=0.3)

            ax2.set_title(f'{shape_name} - Wireframe')
            ax2.set_xlim(mid_x - max_range, mid_x + max_range)
            ax2.set_ylim(mid_y - max_range, mid_y + max_range)
            ax2.set_zlim(mid_z - max_range, mid_z + max_range)
            ax2.view_init(elev=30, azim=45)

        plt.tight_layout()
        fig.suptitle('Dual Contouring Algorithm Results Comparison', fontsize=20, y=0.98)
        fig.savefig(f"{output_dir}/all_shapes_comparison.png", dpi=300, bbox_inches='tight')
        plt.close(fig)

        print(f"\nVisualization complete! Images saved to '{output_dir}/' directory:")
        for vertices, faces, shape_name in valid_shapes:
            print(f"  - {shape_name.lower()}_surface.png: {shape_name} surface representation")
            print(f"  - {shape_name.lower()}_multiple_views.png: {shape_name} multiple viewing angles")
        print(f"  - all_shapes_comparison.png: Comparison of all generated shapes")

def main():
    """Main function to generate all visualizations."""
    visualize_all_shapes()

if __name__ == "__main__":
    main()
