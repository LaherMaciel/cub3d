/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/03 23:28:45 by karocha-         ###   ########.fr       */
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

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}
float	eye_fish(float ray_angle, float dist)
{
	float	angle_diff;
	float	fix_dist;

	angle_diff = ray_angle - game()->player_dir;
	fix_dist = dist * cos(angle_diff);
	return (fix_dist);
}

bool	touch(float px, float py)
{
	int	x;
	int	y;

	x = (int)px;
	y = (int)py;
	if (x < 0 || y < 0 || x >= game()->map_width || y >= game()->map_height)
		return (true);
	if (game()->map[y][x] == '1')
		return (true);
	return (false);
}

void	convert_3D(float ray_x, float ray_y, float ray_angle, int i)
{
	float	dist;
	float	fixed_dist;
	float	height;
	int		py;
	int		end;
	int		y;

	dist = distance(ray_x - game()->player_x, ray_y - game()->player_y);
	if (dist < 0.1)
		dist = 0.1;
	fixed_dist = eye_fish(ray_angle, dist);
	if (fixed_dist < 0.1)
		fixed_dist = 0.1;
	height = (WINDOW_HEIGHT / fixed_dist) * 1;
	py = (WINDOW_HEIGHT / 2) - (height / 2);
	end = py + height;
	if (py < 0)
		py = 0;
	if (end > WINDOW_HEIGHT)
		end = WINDOW_HEIGHT;
	y = 0;
	while (y < py)
		put_pixel(i, y++, game()->colors.ceiling_rgb);
	while (py < end)
		put_pixel(i, py++, COLOR_BLUE);
	y = end;
	while (y < WINDOW_HEIGHT)
		put_pixel(i, y++, game()->colors.floor_rgb);
}

void	put_lines(float ray_angle, int i)
{
	float	ray_x;
	float	ray_y;
	float	step;

	step = 0.05;
	ray_x = game()->player_x;
	ray_y = game()->player_y;
	while (!touch(ray_x, ray_y))
	{
		put_pixel(START_X + (int)(ray_x * BLOCK),
			START_Y + (int)(ray_y * BLOCK), COLOR_RED);
		ray_x += cos(ray_angle) * step;
		ray_y += sin(ray_angle) * step;
	}
	convert_3D(ray_x, ray_y, ray_angle, i);
}

void	fov(void)
{
	int		i;
	float	fov_start;
	float	fov_step;
	float	ray_angle;

	fov_start = game()->player_dir - (PI / 6);
	fov_step = (PI / 3) / WINDOW_WIDTH;
	i = -1;
	while (++i < WINDOW_WIDTH)
	{
		ray_angle = fov_start + (fov_step * i);
		put_lines(ray_angle, i);
	}
}
