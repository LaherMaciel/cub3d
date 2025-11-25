/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/25 17:01:09 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
static t_raycast	cast_single_ray(float angle)
{
	t_raycast	ray;
	float		vars[6];
	int			prev[2];

	init_ray_vars(angle, vars);
	prev[0] = (int)vars[2];
	prev[1] = (int)vars[3];
	while (!is_wall((int)vars[2], (int)vars[3]) && vars[4] < 100)
	{
		vars[2] += vars[0] * vars[5];
		vars[3] += vars[1] * vars[5];
		vars[4] += vars[5];
		update_ray_side(&ray, vars[2], vars[3], prev);
	}
	ray.dist = vars[4];
	ray.hit_x = vars[2];
	ray.hit_y = vars[3];
	ray.dx = vars[0];
	ray.dy = vars[1];
	return (ray);
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
** Draw one vertical line (one column of the screen)
*/
static void	draw_textured_column(int x, float dist, t_raycast *ray)
{
	int		y;
	t_tex	*tex;
	float	wall_h;

	wall_h = WINDOW_HEIGHT / dist;
	tex = select_wall_texture(ray);
	y = 0;
	while (y < WINDOW_HEIGHT / 2 - wall_h / 2)
		put_pixel(x, y++, game()->colors.ceiling_rgb);
	draw_wall_pixels(x, tex, ray, wall_h);
	y = WINDOW_HEIGHT / 2 + wall_h / 2;
	while (y < WINDOW_HEIGHT)
		put_pixel(x, y++, game()->colors.floor_rgb);
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
	int			x;
	float		ray_angle;
	t_raycast	ray;
	float		fixed_distance;
	float		angle_per_pixel;

	angle_per_pixel = (PI / 3.0) / (float)WINDOW_WIDTH;
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray_angle = (game()->player_dir - (PI / 6))
			+ (angle_per_pixel * (float)x);
		ray = cast_single_ray(ray_angle);
		fixed_distance = fix_fisheye(ray.dist, ray_angle);
		if (fixed_distance < 0.05f)
			fixed_distance = 0.05f;
		draw_textured_column(x, fixed_distance, &ray);
		x++;
	}
}
