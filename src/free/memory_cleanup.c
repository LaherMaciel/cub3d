/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/17 13:16:16 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	free_textures(void)
{
	if (game()->textures.no_path)
		free(game()->textures.no_path);
	if (game()->textures.so_path)
		free(game()->textures.so_path);
	if (game()->textures.we_path)
		free(game()->textures.we_path);
	if (game()->textures.ea_path)
		free(game()->textures.ea_path);
	if (game()->textures.roof_path)
		free(game()->textures.roof_path);
	if (game()->textures.floor_path)
		free(game()->textures.floor_path);
	if (game()->textures.weapon_path)
		free(game()->textures.weapon_path);
}

static void	free_map(void)
{
	int	i;

	if (game()->map)
	{
		i = 0;
		while (i < game()->map_height)
		{
			if (game()->map[i])
				free(game()->map[i]);
			i++;
		}
		free(game()->map);
	}
}

void	cleanup_parsing(void)
{
	free_textures();
	free_map();
}

static void	close_game(void)
{
	if (game() == NULL)
		exit(EXIT_SUCCESS);
	if (game()->image)
		mlx_destroy_image(game()->mlx, game()->image);
	if (game()->window)
		mlx_destroy_window(game()->mlx, game()->window);
	if (game()->mlx)
	{
		mlx_destroy_display(game()->mlx);
		free(game()->mlx);
	}
	exit(EXIT_SUCCESS);
}

int	close_program(void)
{
	cleanup_parsing();
	close_game();
	return (0);
}
