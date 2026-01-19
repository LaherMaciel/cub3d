/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_validate_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <lawences@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/01/19 17:35:07 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Finds player position in map and sets game state
// Validates that only one player exists
// Returns 0 on success, 1 on error
static int	find_and_set_player(int i, int j, int *player_count)
{
	if (ft_strchr("NSEW", game()->map[i][j]))
	{
		(*player_count)++;
		if (*player_count > 1)
			return (ft_putstr_fd("Error: Multiple player positions\n", 2), 1);
		game()->player_x = j + 0.5;
		game()->player_y = i + 0.5;
		game()->player_orientation = game()->map[i][j];
		set_player_direction(game()->map[i][j]);
		game()->map[i][j] = '0';
	}
	return (0);
}

// Validates that exactly one player position exists in the map
// Sets player coordinates and orientation
// Returns 0 if valid, 1 if invalid
int	validate_player_position(void)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < game()->map_height)
	{
		j = 0;
		while (j < game()->map_width)
		{
			if (find_and_set_player(i, j, &player_count) != 0)
				return (1);
			j++;
		}
		i++;
	}
	if (player_count == 0)
		return (ft_putstr_fd("Error: No player position found\n", 2), 1);
	return (0);
}

// Main map validation function
// Validates map closure and player position
// Returns 0 on success, 1 on error
int	validate_map(void)
{
	if (flood_fill())
		return (1);
	if (validate_player_position() != 0)
		return (1);
	return (0);
}
