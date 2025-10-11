/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 00:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/01/15 00:00:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
