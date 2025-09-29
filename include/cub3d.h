/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 01:27:56 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/09/29 19:39:36 by lahermaciel      ###   ########.fr       */
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
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

// Define map constants
# define MAP_WIDTH 24
# define MAP_HEIGHT 24

// Define player constants
# define MOVE_SPEED 5.0
# define ROT_SPEED 0.1

// Define colors (RGB values)
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_YELLOW 0xFFFF00

typedef struct s_game
{
	void	*mlx;
	void	*window;
	void	*image;
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		map[MAP_WIDTH][MAP_HEIGHT];
	double	player_x;
	double	player_y;
	double	player_dir; // Angle in radians
}				t_game;

typedef struct s_player
{
	float	player_x;
	float	player_y;
	float	player_dir; // Angle in radians
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	key_rot_left;
	bool	key_rot_right;
}				t_player;

void	init_image(t_game *game);
void	init_game(t_game *game);
void	init_player(t_player *player);
int		key_press(int keycode, t_player *player);
int		key_release(int keycode, t_player *player);
void	move_player_2d(t_player *player);
void	move_player_3d(t_player *player);
int		draw_loop(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);
void	draw_square(t_game *game, int x, int y, int size);

#endif