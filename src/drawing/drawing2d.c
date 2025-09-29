/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:39:10 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/09/29 19:39:23 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	put_pixel(t_game *game, int x, int y, int color)
{
	int	i;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	i = y * game->size_line + x * (game->bpp / 8);
	game->data_addr[i] = color & 0xFF;
	game->data_addr[i + 1] = (color >> 8) & 0xFF;
	game->data_addr[i + 2] = (color >> 16) & 0xFF;
}

void	draw_square(t_game *game, int x, int y, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			put_pixel(game, x + i, y + j, COLOR_GREEN);
	}
	mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
}

int	draw_loop(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
	return (0);
}
