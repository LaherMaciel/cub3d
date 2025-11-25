/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/25 16:57:10 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static unsigned int	get_texture_color(t_tex *tex, int x, int y)
{
	char	*pixel;

	if (x < 0)
		x = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->height)
		y = tex->height - 1;
	pixel = tex->addr + (y * tex->size_line + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

t_tex	*select_wall_texture(t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (ray->dx > 0)
			return (&game()->textures.east);
		else
			return (&game()->textures.west);
	}
	else
	{
		if (ray->dy > 0)
			return (&game()->textures.south);
		else
			return (&game()->textures.north);
	}
}

void	draw_wall_pixels(int x, t_tex *tex, t_raycast *ray, float wall_h)
{
	int		y;
	int		tex_x;
	float	step;
	float	tex_y_f;
	int		top;

	if (ray->side == 0)
		tex_x = (int)((ray->hit_y - floorf(ray->hit_y)) * tex->width);
	else
		tex_x = (int)((ray->hit_x - floorf(ray->hit_x)) * tex->width);
	step = (float)tex->height / wall_h;
	tex_y_f = 0.0f;
	top = WINDOW_HEIGHT / 2 - wall_h / 2;
	if (top < 0)
	{
		tex_y_f = -top * step;
		top = 0;
	}
	y = top;
	while (y < WINDOW_HEIGHT / 2 + wall_h / 2 && y < WINDOW_HEIGHT)
	{
		put_pixel(x, y, get_texture_color(tex, tex_x, (int)tex_y_f));
		tex_y_f += step;
		y++;
	}
}

void	init_ray_vars(float angle, float *vars)
{
	vars[0] = cos(angle);
	vars[1] = sin(angle);
	vars[2] = game()->player_x;
	vars[3] = game()->player_y;
	vars[4] = 0.0f;
	vars[5] = 0.01f;
}

void	update_ray_side(t_raycast *ray, float rx, float ry, int *prev)
{
	int	cell_x;
	int	cell_y;

	cell_x = (int)rx;
	cell_y = (int)ry;
	if (cell_x != prev[0])
		ray->side = 0;
	if (cell_y != prev[1])
		ray->side = 1;
	prev[0] = cell_x;
	prev[1] = cell_y;
}
