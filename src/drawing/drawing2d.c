/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:39:10 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/01 10:55:20 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	put_pixel(int x, int y, int color)
{
	int	i;

	if (x < 0 || x >= WINDOW_WIDTH || y < 0 || y >= WINDOW_HEIGHT)
		return ;
	i = y * game()->size_line + x * (game()->bpp / 8);
	game()->data_addr[i] = color & 0xFF;
	game()->data_addr[i + 1] = (color >> 8) & 0xFF;
	game()->data_addr[i + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
			put_pixel(x + i, y + j, COLOR_GREEN);
	}
	mlx_put_image_to_window(game()->mlx, game()->window, game()->image, 0, 0);
}

int	draw_loop(void)
{
	mlx_put_image_to_window(game()->mlx, game()->window, game()->image, 0, 0);
	return (0);
}
