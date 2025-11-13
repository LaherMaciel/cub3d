/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/04 10:13:19 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** Draw a filled square on the minimap
** Used for drawing walls and player
*/
void	draw_minimap_square(int start_x, int start_y, int size, int color)
{
	int	x;
	int	y;

	y = start_y;
	while (y < start_y + size)
	{
		x = start_x;
		while (x < start_x + size)
		{
			if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
				put_pixel(x, y, color);
			x++;
		}
		y++;
	}
}

/*
** Draws a single ray line from player position to wall on minimap
** Used for visualizing field of view
*/
static void	draw_ray_line(float ray_angle)
{
	float	ray_x;
	float	ray_y;

	ray_x = game()->player_x;
	ray_y = game()->player_y;
	while (!is_wall((int)ray_x, (int)ray_y))
	{
		put_pixel(START_X + (int)(ray_x * BLOCK),
			START_Y + (int)(ray_y * BLOCK), COLOR_RED);
		ray_x += cos(ray_angle) * 0.05;
		ray_y += sin(ray_angle) * 0.05;
	}
}

// Draws multiple rays representing the field of view
// Casts 60 rays across a 60-degree FOV
static void	draw_fov_rays(void)
{
	float	fov_start;
	float	step;
	float	ray_angle;
	float	i;

	fov_start = game()->player_dir - (PI / 6);
	step = (PI / 3) / 60;
	i = 0;
	while (i < 60)
	{
		ray_angle = fov_start + (step * i);
		draw_ray_line(ray_angle);
		i += 0.2;
	}
}

// Draws the player as a square on the minimap
// Positioned at player coordinates with visual representation
static void	draw_player_square(void)
{
	int	player_x;
	int	player_y;
	int	player_size;

	player_size = BLOCK / 2;
	player_x = START_X + (int)(game()->player_x * BLOCK);
	player_x -= player_size / 2;
	player_y = START_Y + (int)(game()->player_y * BLOCK);
	player_y -= player_size / 2;
	draw_minimap_square(player_x, player_y, player_size, COLOR_GREEN);
}

/*
** Draw player and direction ray on minimap
** Shows player position and field of view rays
*/
void	draw_player_on_minimap(void)
{
	draw_fov_rays();
	draw_player_square();
}

/* static void	draw_circle(int x, int y, int size)
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
} */
