# cub3d

[![42](https://img.shields.io/badge/42-Project-blue)](https://42.fr)
[![C](https://img.shields.io/badge/Language-C-green)](https://en.wikipedia.org/wiki/C_(programming_language))

> A 3D raycasting game engine inspired by Wolfenstein 3D, built with MiniLibX.

## Overview

`cub3d` is a 42 School Rank 4 project, built in collaboration. The goal is to implement a first-person 3D game engine using raycasting: given a 2D map, the engine renders walls with textures and depth in real time, simulating a 3D perspective.

## Usage

```bash
make
./cub3d map.cub
```

## Map format (`.cub`)

| Element | Identifier | Description |
|---------|------------|-------------|
| North texture | `NO ./path` | Wall texture facing north |
| South texture | `SO ./path` | Wall texture facing south |
| West texture | `WE ./path` | Wall texture facing west |
| East texture | `EA ./path` | Wall texture facing east |
| Floor color | `F R,G,B` | Floor RGB color |
| Ceiling color | `C R,G,B` | Ceiling RGB color |

Map grid characters:

| Character | Meaning |
|-----------|---------|
| `0` | Empty space |
| `1` | Wall |
| `N` / `S` / `E` / `W` | Player start position and orientation |

The map must be enclosed by walls and contain exactly one player start position.

## Controls

| Key | Action |
|-----|--------|
| `W A S D` | Move |
| `←` `→` | Rotate camera |
| `ESC` | Exit |

## Project structure

```
cub3d/
├── src/               # Source files
├── include/
│   └── cub3d.h
├── libraries/
│   ├── libft/
│   └── minilibx-linux/
└── Makefile
```

## Make targets

| Target | Description |
|--------|-------------|
| `make` | Build the binary |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and binary |
| `make re` | Rebuild from scratch |
| `make norm` | Run norminette |

## Authors

**Laher Maciel**
- GitHub: [@LaherMaciel](https://github.com/LaherMaciel)
- 42 Login: lawences

**Kayki Rocha**
- GitHub: [@UnderOfAll](https://github.com/UnderOfAll)
- 42 Login: karocha-
