/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:18:25 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/13 14:33:48 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Main map initialization function
// Parses the .cub file and loads textures
void	init_map(char *filename)
{
	ft_printf("Loading map: %s...\n", filename);
	parse_cub_file(filename);
	get_textures();
	ft_printf("Map loaded successfully!\n");
	ft_printf("Map dimensions: %dx%d\n", game()->map_width, game()->map_height);
	ft_printf("Player position: (%.1f, %.1f) facing %c\n",
		game()->player_x, game()->player_y, game()->player_orientation);
}
