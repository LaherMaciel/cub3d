/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/04 10:07:33 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Raytracing functions will be implemented here
// This includes:
// - Ray casting algorithm
// - 3D wall rendering
// - Texture mapping
// - Sprite rendering
// - Distance calculations

/*
** Is there a wall at this map position?
*/
bool	is_wall(int x, int y)
{
	if (x < 0 || y < 0 || x >= game()->map_width || y >= game()->map_height)
		return (true);
	if (game()->map[y][x] == '1')
		return (true);
	return (false);
}

/*
** Cast one ray and return the distance to the wall
** This is your ORIGINAL simple approach but with ONE key fix
*/
static float	cast_single_ray(float ray_angle)
{
	float	ray_x;
	float	ray_y;
	float	step_x;
	float	step_y;
	float	distance;

	ray_x = game()->player_x;
	ray_y = game()->player_y;
	step_x = cos(ray_angle) * 0.005;
	step_y = sin(ray_angle) * 0.005;
	distance = 0;
	while (!is_wall((int)ray_x, (int)ray_y))
	{
		ray_x += step_x;
		ray_y += step_y;
		distance += 0.005;
		if (distance > 100)
			break ;
	}
	return (distance);
}

/*
** Draw one vertical line (one column of the screen)
*/
static void	draw_column(int x, float distance)
{
	float	wall_height;
	int		wall_top;
	int		wall_bottom;
	int		y;

	wall_height = WINDOW_HEIGHT / distance;
	wall_top = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	wall_bottom = (WINDOW_HEIGHT / 2) + (wall_height / 2);
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom > WINDOW_HEIGHT)
		wall_bottom = WINDOW_HEIGHT;
	y = 0;
	while (y < wall_top)
		put_pixel(x, y++, COLOR_CYAN_LIGHT);
	while (y < wall_bottom)
		put_pixel(x, y++, COLOR_PURPLE_LIGHT);
	while (y < WINDOW_HEIGHT)
		put_pixel(x, y++, COLOR_YELLOW_DARK);
}

/*
** THE MAGIC FUNCTION - Fixes fisheye
** 
** What's happening:
** - Imagine you're looking straight ahead
** - A ray going left at 30° travels FURTHER to hit the wall
** - But it LOOKS the same distance as the center ray
** - cos(angle_diff) makes far rays shorter = no fisheye!
*/
static float	fix_fisheye(float distance, float ray_angle)
{
	float	angle_diff;

	angle_diff = ray_angle - game()->player_dir;
	return (distance * cos(angle_diff));
}

/*
** Main function - cast all rays across the screen
** 
** Step by step:
** 1. Loop through each column of the screen (left to right)
** 2. Calculate the angle for that column's ray
** 3. Cast the ray and get distance
** 4. Fix the fisheye effect
** 5. Draw the wall column
*/
void	fov(void)
{
	int		x;
	float	ray_angle;
	float	raw_distance;
	float	fixed_distance;
	float	angle_per_pixel;

	angle_per_pixel = (PI / 3.0) / (float)WINDOW_WIDTH;
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray_angle = (game()->player_dir - (PI / 6))
			+ (angle_per_pixel * (float)x);
		raw_distance = cast_single_ray(ray_angle);
		fixed_distance = fix_fisheye(raw_distance, ray_angle);
		if (fixed_distance < 0.1)
			fixed_distance = 0.1;
		draw_column(x, fixed_distance);
		x++;
	}
}
