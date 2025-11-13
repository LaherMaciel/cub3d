/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/13 14:31:20 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Loads all texture images from their file paths
// Exits with error if any texture fails to load
void	get_textures(void)
{
	t_game	*g;

	ft_printf("Loading textures...\n");
	g = game();
	g->textures.no_img = mlx_xpm_file_to_image(g->mlx,
			g->textures.no_path, &g->textures.no_width,
			&g->textures.no_height);
	if (!g->textures.no_img)
		error_exit("Failed to load north texture\n", 1);
	g->textures.so_img = mlx_xpm_file_to_image(g->mlx,
			g->textures.so_path, &g->textures.so_width,
			&g->textures.so_height);
	if (!g->textures.so_img)
		error_exit("Failed to load south texture\n", 1);
	g->textures.we_img = mlx_xpm_file_to_image(g->mlx,
			g->textures.we_path, &g->textures.we_width,
			&g->textures.we_height);
	if (!g->textures.we_img)
		error_exit("Failed to load west texture\n", 1);
	g->textures.ea_img = mlx_xpm_file_to_image(g->mlx,
			g->textures.ea_path, &g->textures.ea_width,
			&g->textures.ea_height);
	if (!g->textures.ea_img)
		error_exit("Failed to load east texture\n", 1);
}
