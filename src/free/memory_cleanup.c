/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/13 14:31:20 by lahermaciel      ###   ########.fr       */
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
	if (g->textures.no_path)
		free(g->textures.no_path);
	if (g->textures.so_path)
		free(g->textures.so_path);
	if (g->textures.we_path)
		free(g->textures.we_path);
	if (g->textures.ea_path)
		free(g->textures.ea_path);
	if (g->textures.roof_path)
		free(g->textures.roof_path);
	if (g->textures.floor_path)
		free(g->textures.floor_path);
	g->textures.no_path = NULL;
	g->textures.so_path = NULL;
	g->textures.we_path = NULL;
	g->textures.ea_path = NULL;
	g->textures.roof_path = NULL;
	g->textures.floor_path = NULL;
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
		if (g->textures.no_img)
			mlx_destroy_image(g->mlx, g->textures.no_img);
		if (g->textures.so_img)
			mlx_destroy_image(g->mlx, g->textures.so_img);
		if (g->textures.we_img)
			mlx_destroy_image(g->mlx, g->textures.we_img);
		if (g->textures.ea_img)
			mlx_destroy_image(g->mlx, g->textures.ea_img);
		if (g->textures.roof_img)
			mlx_destroy_image(g->mlx, g->textures.roof_img);
		if (g->textures.floor_img)
			mlx_destroy_image(g->mlx, g->textures.floor_img);
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
void	error_exit(char *message, int code)
{
	if (message != NULL && ft_strlen(message) > 0)
		ft_putstr_fd(message, 2);
	free_all();
	if (game()->image && game()->mlx)
		mlx_destroy_image(game()->mlx, game()->image);
	if (game()->window && game()->mlx)
		mlx_destroy_window(game()->mlx, game()->window);
	if (game()->mlx)
	{
		mlx_destroy_display(game()->mlx);
		free(game()->mlx);
	}
	exit(code);
}
