/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_validate_helpers.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/13 14:33:48 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Validates that map borders are closed (only walls or spaces)
// Returns 0 if valid, 1 if invalid
static int	check_borders(void)
{
	int	i;

	i = 0;
	while (i < game()->map_width)
	{
		if (game()->map[0][i] != '1' && game()->map[0][i] != ' ')
			return (ft_putstr_fd("Error: Map not closed at top\n", 2), 1);
		if (game()->map[game()->map_height - 1][i] != '1'
			&& game()->map[game()->map_height - 1][i] != ' ')
			return (ft_putstr_fd("Error: Map not closed at bottom\n", 2), 1);
		i++;
	}
	i = 0;
	while (i < game()->map_height)
	{
		if (game()->map[i][0] != '1' && game()->map[i][0] != ' ')
			return (ft_putstr_fd("Error: Map not closed at left\n", 2), 1);
		if (game()->map[i][game()->map_width - 1] != '1'
			&& game()->map[i][game()->map_width - 1] != ' ')
			return (ft_putstr_fd("Error: Map not closed at right\n", 2), 1);
		i++;
	}
	return (0);
}

// Validates that interior map cells are properly closed
// Checks that walkable cells (0, N, S, E, W) are not adjacent to spaces
// Returns 0 if valid, 1 if invalid
static int	check_interior(void)
{
	int	i;
	int	j;

	i = 1;
	while (i < game()->map_height - 1)
	{
		j = 1;
		while (j < game()->map_width - 1)
		{
			if (game()->map[i][j] == '0'
				|| ft_strchr("NSEW", game()->map[i][j]))
			{
				if (game()->map[i - 1][j] == ' '
					|| game()->map[i + 1][j] == ' '
					|| game()->map[i][j - 1] == ' '
					|| game()->map[i][j + 1] == ' ')
					return (ft_putstr_fd("Error: Map not properly closed\n",
							2), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

// Validates that the map is properly closed (no gaps)
// Checks both borders and interior cells
// Returns 0 if valid, 1 if invalid
int	validate_map_closed(void)
{
	if (check_borders() != 0)
		return (1);
	if (check_interior() != 0)
		return (1);
	return (0);
}

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
