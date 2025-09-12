# Cub3D

A 3D raycasting game engine inspired by the legendary Wolfenstein 3D, built from scratch using the MiniLibX graphics library.

## Overview

Cub3D is a 42 School project that involves creating a 3D game engine using raycasting techniques. The project demonstrates understanding of computer graphics, mathematics, and C programming.

## Features

- **3D Raycasting Engine**: Real-time 3D rendering using raycasting algorithm
- **Texture Mapping**: Support for textured walls and sprites
- **Player Movement**: Smooth first-person movement with collision detection
- **Map Parsing**: Custom map format with configurable textures and colors
- **MiniLibX Integration**: Uses 42's MiniLibX for window management and graphics

## Installation

### Prerequisites

- GCC compiler
- MiniLibX library (42 School graphics library)
- Make

### Building

```bash
make
```

This will create the `cub3D` executable.

## Usage

```bash
./cub3D map.cub
```

Where `map.cub` is a valid map file following the cub3d format specification.

## Map Format

The `.cub` file format includes:

- **Textures**: Paths to wall and sprite textures
- **Colors**: Floor and ceiling colors
- **Map**: 2D grid representing the game world
  - `0`: Empty space
  - `1`: Wall
  - `N/S/E/W`: Player starting position and orientation
  - `2`: Collectible sprite

## Controls

- **WASD**: Move forward/backward/left/right
- **Arrow Keys**: Rotate camera
- **ESC**: Exit game

## Project Structure

```
cub3d/
├── src/           # Source code
├── includes/      # Header files
├── maps/          # Example map files
├── textures/      # Texture files
├── Makefile       # Build configuration
└── README.md      # This file
```

## Technical Details

- **Language**: C
- **Graphics Library**: MiniLibX
- **Rendering**: Raycasting algorithm
- **Platform**: Linux/macOS

## Development

This project is part of the 42 School curriculum and demonstrates:

- C programming proficiency
- Computer graphics understanding
- Mathematical concepts (trigonometry, linear algebra)
- Software architecture and design patterns

## Screenshots

*Screenshots will be added once the project is complete*

## Author

[Your Name] - 42 School Student

## Acknowledgments

- 42 School for providing the project specification
- MiniLibX development team
- The original Wolfenstein 3D for inspiration
