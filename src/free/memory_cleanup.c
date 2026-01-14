/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/01/14 23:05:27 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Frees all texture path strings allocated during parsing
static void	free_textures(void)
{
	t_game	*g;

	g = game();
	if (!g)
		return ;
	if (g->textures.north.path)
		free(g->textures.north.path);
	if (g->textures.south.path)
		free(g->textures.south.path);
	if (g->textures.west.path)
		free(g->textures.west.path);
	if (g->textures.east.path)
		free(g->textures.east.path);
	if (g->textures.roof.path)
		free(g->textures.roof.path);
	if (g->textures.floor.path)
		free(g->textures.floor.path);
	g->textures.north.path = NULL;
	g->textures.south.path = NULL;
	g->textures.west.path = NULL;
	g->textures.east.path = NULL;
	g->textures.roof.path = NULL;
	g->textures.floor.path = NULL;
}

// Frees the map array and all its lines
static void	free_map(void)
{
	int		i;
	t_game	*g;

	g = game();
	if (g->map)
	{
		i = 0;
		while (i < g->map_height)
		{
			if (g->map[i])
			{
				free(g->map[i]);
				g->map[i] = NULL;
			}
			i++;
		}
		free(g->map);
		g->map = NULL;
	}
}

void	free_all_2(t_game	*g)
{
	if (g->textures.west.img)
	{
		mlx_destroy_image(g->mlx, g->textures.west.img);
		g->textures.west.img = NULL;
	}
	if (g->textures.east.img)
	{
		mlx_destroy_image(g->mlx, g->textures.east.img);
		g->textures.east.img = NULL;
	}
	if (g->textures.roof.img)
	{
		mlx_destroy_image(g->mlx, g->textures.roof.img);
		g->textures.roof.img = NULL;
	}
	if (g->textures.floor.img)
	{
		mlx_destroy_image(g->mlx, g->textures.floor.img);
		g->textures.floor.img = NULL;
	}
}

// Frees all allocated resources: texture images, texture paths, and map
// Safe to call multiple times (idempotent)
void	free_all(void)
{
	t_game	*g;

	g = game();
	if (g == NULL)
		return ;
	if (g && g->mlx)
	{
		if (g->textures.north.img)
		{
			mlx_destroy_image(g->mlx, g->textures.north.img);
			g->textures.north.img = NULL;
		}
		if (g->textures.south.img)
		{
			mlx_destroy_image(g->mlx, g->textures.south.img);
			g->textures.south.img = NULL;
		}
		free_all_2(g);
	}
	free_textures();
	free_map();
}

// Called when the window is closed
// Performs cleanup and exits the program
int	close_program(void)
{
	t_game	*g;

	free_all();
	g = game();
	if (g == NULL)
		exit(EXIT_SUCCESS);
	if (g->image)
		mlx_destroy_image(g->mlx, g->image);
	if (g->window)
		mlx_destroy_window(g->mlx, g->window);
	if (g->mlx)
	{
		mlx_destroy_display(g->mlx);
		free(g->mlx);
	}
	exit(EXIT_SUCCESS);
}

// Prints the error message (if provided) and exits the program
// freeing all needed resources. If message is NULL or empty,
// only cleanup is performed (useful when error already printed)