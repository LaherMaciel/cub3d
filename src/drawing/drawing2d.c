/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:39:10 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/15 14:18:53 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	put_pixel(int x, int y, int color)
{
	int	i;

	if (x < 0 || x >= game()->window_width || y < 0
		|| y >= game()->window_height)
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
	while (i < game()->window_width * game()->window_height * (game()->bpp / 8))
	{
		game()->data_addr[i] = 0;
		game()->data_addr[i + 1] = 0;
		game()->data_addr[i + 2] = 0;
		i += game()->bpp / 8;
	}
}

static void	draw_map_cell(int x, int y, int cell_size, char cell_type)
{
	int	k;
	int	l;

	k = 0;
	while (k < cell_size)
	{
		l = 0;
		while (l < cell_size)
		{
			if (cell_type == '1')
				put_pixel(x + l, y + k, COLOR_BLUE);
			else
				put_pixel(x + l, y + k, COLOR_BLACK);
			l++;
		}
		k++;
	}
}

static void	draw_map_rows(int cell_size, int start_x, int start_y)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < game()->map_height)
	{
		j = 0;
		while (j < game()->map_width)
		{
			x = start_x + j * cell_size;
			y = start_y + i * cell_size;
			if (game()->map[i][j] == '1' || game()->map[i][j] == '0'
				|| game()->map[i][j] == ' ')
				draw_map_cell(x, y, cell_size, game()->map[i][j]);
			j++;
		}
		i++;
	}
}

void	draw_map_2d(void)
{
	int	cell_size;
	int	start_x;
	int	start_y;

	if (!game()->map)
		return ;
	cell_size = 20;
	start_x = 50;
	start_y = 50;
	draw_map_rows(cell_size, start_x, start_y);
	draw_map_grid();
	draw_player_position();
}
