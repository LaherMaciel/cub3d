/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/03 20:23:53 by karocha-         ###   ########.fr       */
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

	draw_horizontal_grid_lines(BLOCK, START_X, START_Y);
	draw_vertical_grid_lines(BLOCK, START_X, START_Y);
}

void	draw_player_position(void)
{
	int	player_x;
	int	player_y;

	player_x = START_X + (int)(game()->player_x * BLOCK);
	player_y = START_Y + (int)(game()->player_y * BLOCK);
	draw_circle(player_x, player_y, 8);
}
