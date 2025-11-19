/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/18 11:07:20 by karocha-         ###   ########.fr       */
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
static t_raycast cast_single_ray(float angle)
{
	t_raycast ray;
	float dx = cos(angle);
	float dy = sin(angle);

	float rx = game()->player_x;
	float ry = game()->player_y;

	float dist = 0.0f;
	float step = 0.01f;

	int prev_x = (int)rx;
	int prev_y = (int)ry;

	while (!is_wall((int)rx, (int)ry) && dist < 100)
	{
		rx += dx * step;
		ry += dy * step;
		dist += step;

		int cell_x = (int)rx;
		int cell_y = (int)ry;

		if (cell_x != prev_x)
			ray.side = 0;     // vertical wall
		if (cell_y != prev_y)
			ray.side = 1;     // horizontal wall

		prev_x = cell_x;
		prev_y = cell_y;
	}

	ray.dist  = dist;
	ray.hit_x = rx;
	ray.hit_y = ry;
	ray.dx    = dx;
	ray.dy    = dy;
	return ray;
}



static int get_texture_x(t_tex *t, t_raycast *ray)
{
	float fx;

	if (ray->side == 0)   // vertical wall → use Y hit
		fx = ray->hit_y - floorf(ray->hit_y);
	else                  // horizontal wall → use X hit
		fx = ray->hit_x - floorf(ray->hit_x);

	return (int)(fx * t->width);
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

static t_tex *select_wall_texture(t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (ray->dx > 0)
			return &game()->textures.east;
		else
			return &game()->textures.west;
	}
	else
	{
		if (ray->dy > 0)
			return &game()->textures.south;
		else
			return &game()->textures.north;
	}
}

/*
** Draw one vertical line (one column of the screen)
*/
static void	draw_textured_column(int x, float dist, t_raycast *ray)
{
	t_tex	*tex = select_wall_texture(ray);
	float	wall_h = WINDOW_HEIGHT / dist;
	int		top = WINDOW_HEIGHT / 2 - wall_h / 2;
	int		bot = WINDOW_HEIGHT / 2 + wall_h / 2;
	int		y;
	int		tex_x = get_texture_x(tex, ray);
	float	step = (float)tex->height / wall_h;
	float	tex_y_f;

	tex_y_f = 0.0f;
	if (top < 0)
	{
		tex_y_f = -top * step;
		top = 0;
	}
	if (bot > WINDOW_HEIGHT)
		bot = WINDOW_HEIGHT;

	y = 0;
	while (y < top)
		put_pixel(x, y++, game()->colors.ceiling_rgb);

	while (y < bot)
	{
		int tex_y = (int)tex_y_f;
		unsigned int color = get_texture_color(tex, tex_x, tex_y);
		put_pixel(x, y, color);
		tex_y_f += step;
		y++;
	}

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
