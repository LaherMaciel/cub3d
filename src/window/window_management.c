/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/17 13:28:37 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Updates window size based on screen dimensions
// Uses screen size if larger than default, otherwise uses default
void	update_window_size(void)
{
	int	screen_width;
	int	screen_height;

	mlx_get_screen_size(game()->mlx, &screen_width, &screen_height);
	if (screen_width > WINDOW_WIDTH || screen_height > WINDOW_HEIGHT)
	{
		game()->window_width = screen_width;
		game()->window_height = screen_height;
	}
	else
	{
		game()->window_width = WINDOW_WIDTH;
		game()->window_height = WINDOW_HEIGHT;
	}
}

// Handles window resize events
// Recreates image buffer when window is resized
int	handle_window_resize(int event, void *param)
{
	(void)param;
	if (event == 22)
	{
		update_window_size();
		if (game()->image)
			mlx_destroy_image(game()->mlx, game()->image);
		init_image();
		game()->data_addr = mlx_get_data_addr(game()->image, &game()->bpp,
			&game()->size_line, &game()->endian);
	}
	return (0);
}

// Toggles between windowed and fullscreen mode
// Recreates window and image buffer accordingly
void	toggle_fullscreen(void)
{
	if (game()->is_fullscreen)
	{
		game()->window = mlx_new_window(game()->mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub3d");
		game()->window_width = WINDOW_WIDTH;
		game()->window_height = WINDOW_HEIGHT;
		game()->is_fullscreen = false;
	}
	else
	{
		mlx_destroy_window(game()->mlx, game()->window);
		update_window_size();
		game()->window = mlx_new_window(game()->mlx, game()->window_width,
			game()->window_height, "cub3d");
		game()->is_fullscreen = true;
	}
	if (game()->image)
		mlx_destroy_image(game()->mlx, game()->image);
	init_image();
	game()->data_addr = mlx_get_data_addr(game()->image, &game()->bpp,
		&game()->size_line, &game()->endian);
	setup_window_hooks();
}
