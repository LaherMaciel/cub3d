/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 01:27:56 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/09/13 02:06:04 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

// MLX includes
# include "../libraries/minilibx-linux/mlx.h"

// Libft includes
# include "../libraries/libft/include/libft.h"

// Define window dimensions
# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768

// Define map constants
# define MAP_WIDTH 24
# define MAP_HEIGHT 24

// Define player constants
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.1

// Define colors (RGB values)
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_YELLOW 0xFFFF00

#endif