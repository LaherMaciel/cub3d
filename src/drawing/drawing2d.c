/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:39:10 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/01 22:27:28 by lahermaciel      ###   ########.fr       */
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

void	clear_screen(void)
{
	int	i;

	i = 0;
	while (i < WINDOW_WIDTH * WINDOW_HEIGHT * (game()->bpp / 8))
	{
		game()->data_addr[i] = 0;
		game()->data_addr[i + 1] = 0;
		game()->data_addr[i + 2] = 0;
		i += game()->bpp / 8;
	}
}

void	draw_circle(int x, int y, int size)
{
	int	radius;
	int	i;
	int	j;
	int	dx;
	int	dy;

	radius = size / 2;
	i = -radius;
	while (i <= radius)
	{
		j = -radius;
		while (j <= radius)
		{
			dx = i;
			dy = j;
			if (dx * dx + dy * dy <= radius * radius)
				put_pixel(x + i, y + j, COLOR_GREEN);
			j++;
		}
		i++;
	}
}
