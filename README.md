# Cub3D

[![42 School](https://img.shields.io/badge/42-School-blue)](https://42.fr/)
[![Language](https://img.shields.io/badge/Language-C-orange)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/Platform-Linux-green)](https://www.linux.org/)
[![Status](https://img.shields.io/badge/Status-In_Development-yellow)]()

A 3D raycasting game engine inspired by the legendary Wolfenstein 3D, built from scratch using the MiniLibX graphics library.

## Overview

Cub3D is a 42 School project that involves creating a 3D game engine using raycasting techniques. This project demonstrates understanding of computer graphics, mathematics, and C programming. The engine renders a 3D world from a 2D map using raycasting algorithms, similar to the original Wolfenstein 3D.

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
- X11 libraries (for Linux)

### Building

```bash
make
```

This will create the `cub3d` executable.

### Available Make Targets

- `make` or `make all` - Build the project
- `make clean` - Remove object files
- `make fclean` - Remove all generated files
- `make re` - Rebuild from scratch
- `make run` - Build and run the program
- `make norm` - Check code style with norminette
- `make help` - Show all available targets

## Usage

```bash
./cub3d map.cub
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
├── src/                           # Project source code
├── include/                       # Project header files
│   └── cub3d.h                   # Main header file
├── libraries/                     # External libraries
│   ├── libft/                    # Custom C library
│   │   ├── src/                  # Libft source files
│   │   └── include/              # Libft headers
│   └── minilibx-linux/           # Graphics library
├── objects/                       # Compiled object files
├── Makefile                       # Build configuration
├── .gitignore                     # Git ignore rules
└── README.md                      # This file
```

## Technical Details

- **Language**: C
- **Graphics Library**: MiniLibX
- **Custom Library**: Libft (42 School standard library)
- **Rendering**: Raycasting algorithm
- **Platform**: Linux (WSL2 compatible)
- **Build System**: Make
- **Code Style**: Norminette compliant

## Development

This project is part of the 42 School curriculum and demonstrates:

- C programming proficiency
- Computer graphics understanding
- Mathematical concepts (trigonometry, linear algebra)
- Software architecture and design patterns

## Screenshots

*Screenshots will be added once the project is complete*

## Author

**lahermaciel** - 42 School Student

GitHub: [@lahermaciel](https://github.com/lahermaciel)

## Acknowledgments

- 42 School for providing the project specification
- MiniLibX development team
- The original Wolfenstein 3D for inspiration
