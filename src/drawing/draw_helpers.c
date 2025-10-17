/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/17 13:08:01 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	draw_circle(int x, int y, int size)
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

static void	draw_horizontal_grid_lines(int cell_size, int start_x, int start_y)
{
	int	i;
	int	j;

	i = 0;
	while (i <= game()->map_height)
	{
		j = 0;
		while (j < game()->map_width * cell_size)
		{
			put_pixel(start_x + j, start_y + i * cell_size, COLOR_YELLOW);
			j++;
		}
		i++;
	}
}

static void	draw_vertical_grid_lines(int cell_size, int start_x, int start_y)
{
	int	i;
	int	j;

	i = 0;
	while (i <= game()->map_width)
	{
		j = 0;
		while (j < game()->map_height * cell_size)
		{
			put_pixel(start_x + i * cell_size, start_y + j, COLOR_YELLOW);
			j++;
		}
		i++;
	}
}

void	draw_map_grid(void)
{
	int	cell_size;
	int	start_x;
	int	start_y;

	cell_size = 20;
	start_x = 50;
	start_y = 50;
	draw_horizontal_grid_lines(cell_size, start_x, start_y);
	draw_vertical_grid_lines(cell_size, start_x, start_y);
}

void	draw_player_position(void)
{
	int	cell_size;
	int	start_x;
	int	start_y;
	int	player_x;
	int	player_y;

	cell_size = 20;
	start_x = 50;
	start_y = 50;
	player_x = start_x + (int)(game()->player_x * cell_size);
	player_y = start_y + (int)(game()->player_y * cell_size);
	draw_circle(player_x, player_y, 8);
}
