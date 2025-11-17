/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/17 12:48:37 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Loads all texture images from their file paths
// Exits with error if any texture fails to load

/* void	get_textures(void)
{
	t_game	*g;

	ft_printf("Loading textures...\n");
	g = game();
	g->textures.north.img = mlx_xpm_file_to_image(g->mlx,
			g->textures.north.path, &g->textures.north.width,
			&g->textures.north.height);
	if (!g->textures.north.img)
		error_exit("Failed to load north texture\n", 1);
	g->textures.north.addr = mlx_get_data_addr(g->textures.north.img,
			&g->textures.north.bpp, &g->textures.north.size_line,
			&g->textures.north.endian);
	g->textures.south.img = mlx_xpm_file_to_image(g->mlx,
			g->textures.south.path, &g->textures.south.width,
			&g->textures.south.height);
	if (!g->textures.south.img)
		error_exit("Failed to load south texture\n", 1);
	g->textures.south.addr = mlx_get_data_addr(g->textures.south.img,
			&g->textures.south.bpp, &g->textures.south.size_line,
			&g->textures.south.endian);
	g->textures.west.img = mlx_xpm_file_to_image(g->mlx,
			g->textures.west.path, &g->textures.west.width,
			&g->textures.west.height);
	if (!g->textures.west.img)
		error_exit("Failed to load west texture\n", 1);
	g->textures.west.addr = mlx_get_data_addr(g->textures.west.img,
			&g->textures.west.bpp, &g->textures.west.size_line,
			&g->textures.west.endian);
	g->textures.east.img = mlx_xpm_file_to_image(g->mlx,
			g->textures.east.path, &g->textures.east.width,
			&g->textures.east.height);
	if (!g->textures.east.img)
		error_exit("Failed to load east texture\n", 1);
	g->textures.east.addr = mlx_get_data_addr(g->textures.east.img,
			&g->textures.east.bpp, &g->textures.east.size_line,
			&g->textures.east.endian);
} */

void	get_north(void)
{
	t_game	*g;

	g = game();
	g->textures.north.img = mlx_xpm_file_to_image(g->mlx,
			g->textures.north.path, &g->textures.north.width,
			&g->textures.north.height);
	if (!g->textures.north.img)
		error_exit("Failed to load north texture\n", 1);
	g->textures.north.addr = mlx_get_data_addr(g->textures.north.img,
			&g->textures.north.bpp, &g->textures.north.size_line,
			&g->textures.north.endian);
	if (!g->textures.north.addr)
		error_exit("Failed to load north texture data Address\n", 1);
}

void	get_south(void)
{
	t_game	*g;

	g = game();
	g->textures.south.img = mlx_xpm_file_to_image(g->mlx,
			g->textures.south.path, &g->textures.south.width,
			&g->textures.south.height);
	if (!g->textures.south.img)
		error_exit("Failed to load south texture\n", 1);
	g->textures.south.addr = mlx_get_data_addr(g->textures.south.img,
			&g->textures.south.bpp, &g->textures.south.size_line,
			&g->textures.south.endian);
	if (!g->textures.south.addr)
		error_exit("Failed to load south texture data Address\n", 1);
}

void	get_west(void)
{
	t_game	*g;

	g = game();
	g->textures.west.img = mlx_xpm_file_to_image(g->mlx,
			g->textures.west.path, &g->textures.west.width,
			&g->textures.west.height);
	if (!g->textures.west.img)
		error_exit("Failed to load west texture\n", 1);
	g->textures.west.addr = mlx_get_data_addr(g->textures.west.img,
			&g->textures.west.bpp, &g->textures.west.size_line,
			&g->textures.west.endian);
	if (!g->textures.west.addr)
		error_exit("Failed to load west texture data Address\n", 1);
}

void	get_east(void)
{
	t_game	*g;

	g = game();
	g->textures.east.img = mlx_xpm_file_to_image(g->mlx,
			g->textures.east.path, &g->textures.east.width,
			&g->textures.east.height);
	if (!g->textures.east.img)
		error_exit("Failed to load east texture\n", 1);
	g->textures.east.addr = mlx_get_data_addr(g->textures.east.img,
			&g->textures.east.bpp, &g->textures.east.size_line,
			&g->textures.east.endian);
	if (!g->textures.east.addr)
		error_exit("Failed to load east texture data Address\n", 1);
}

void	get_textures(void)
{
	get_north();
	get_south();
	get_west();
	get_east();
}
