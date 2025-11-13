/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:35:11 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/13 14:33:48 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Initializes the MLX window with default dimensions
// Exits on error
void	init_window(void)
{
	game()->window = mlx_new_window(game()->mlx, WINDOW_WIDTH,
		WINDOW_HEIGHT, "cub3d");
	if (!game()->window)
	{
		ft_printf("Error creating window: %s\n", strerror(errno));
		free(game()->mlx);
		exit(EXIT_FAILURE);
	}
	game()->window_width = WINDOW_WIDTH;
	game()->window_height = WINDOW_HEIGHT;
	game()->is_fullscreen = false;
}

// Initializes the MLX image buffer for rendering
// Exits on error
void	init_image(void)
{
	game()->bpp = 0;
	game()->size_line = 0;
	game()->endian = 0;
	game()->image = mlx_new_image(game()->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game()->image)
	{
		ft_printf("Error creating image: %s\n", strerror(errno));
		mlx_destroy_window(game()->mlx, game()->window);
		free(game()->mlx);
		exit(EXIT_FAILURE);
	}
}

// Initializes the MLX library, window, and image buffer
// Sets up the data address for pixel manipulation
void	init_game(void)
{
	game()->mlx = mlx_init();
	if (!game()->mlx)
	{
		ft_printf("Error initializing MLX: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	init_window();
	init_image();
	game()->data_addr = mlx_get_data_addr(game()->image, &game()->bpp,
		&game()->size_line, &game()->endian);
	mlx_put_image_to_window(game()->mlx, game()->window, game()->image, 0, 0);
}

// Initializes player input state (all keys released)
void	init_player(void)
{
	player()->key_up = false;
	player()->key_down = false;
	player()->key_left = false;
	player()->key_right = false;
	player()->key_rot_left = false;
	player()->key_rot_right = false;
	player()->key_shift = false;
}

// Initializes all configuration variables to default values
// Called before parsing to ensure clean state
void	init_config_parsing(void)
{
	game()->textures.no_path = NULL;
	game()->textures.so_path = NULL;
	game()->textures.we_path = NULL;
	game()->textures.ea_path = NULL;
	game()->textures.roof_path = NULL;
	game()->textures.floor_path = NULL;
	game()->colors.floor_rgb = 0;
	game()->colors.ceiling_rgb = 0;
	game()->map = NULL;
	game()->map_width = 0;
	game()->map_height = 0;
	game()->player_x = 0.0;
	game()->player_y = 0.0;
	game()->player_orientation = '\0';
}
