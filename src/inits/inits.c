/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:35:11 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/10 16:38:41 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_image(void)
{
	game()->bpp = 0;
	game()->size_line = 0;
	game()->endian = 0;
	game()->image = mlx_new_image(game()->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game()->image)
	{
		ft_printf("Error creating image: %s\n", strerror(errno));
		free(game()->window);
		free(game()->mlx);
		exit(EXIT_FAILURE);
	}
}

void	init_game(void)
{
	game()->mlx = mlx_init();
	if (!game()->mlx)
	{
		ft_printf("Error initializing MLX: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	game()->window = mlx_new_window(game()->mlx, WINDOW_WIDTH,
		WINDOW_HEIGHT, "cub3d");
	if (!game()->window)
	{
		ft_printf("Error creating window: %s\n", strerror(errno));
		free(game()->mlx);
		exit(EXIT_FAILURE);
	}
	init_image();
	game()->data_addr = mlx_get_data_addr(game()->image, &game()->bpp,
		&game()->size_line, &game()->endian);
	mlx_put_image_to_window(game()->mlx, game()->window, game()->image, 0, 0);
}

void	init_player(void)
{
	player()->player_x = WINDOW_WIDTH / 2;
	player()->player_y = WINDOW_HEIGHT / 2;
	player()->player_dir = 0.0;
	player()->key_up = false;
	player()->key_down = false;
	player()->key_left = false;
	player()->key_right = false;
	player()->key_rot_left = false;
	player()->key_rot_right = false;
}
