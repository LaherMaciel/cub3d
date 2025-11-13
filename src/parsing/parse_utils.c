/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/03 21:01:36 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Converts RGB values to a single integer color value
// Format: (R << 16) | (G << 8) | B
int	convert_rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

// Checks if a line contains only valid map characters
// Valid characters: 0, 1, N, S, E, W, space
bool	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

// Sets player direction angle based on orientation character
// N = -PI/2, S = PI/2, E = 0, W = PI
void	set_player_direction(char orientation)
{
	if (orientation == 'N')
		game()->player_dir = -PI / 2;
	else if (orientation == 'S')
		game()->player_dir = PI / 2;
	else if (orientation == 'E')
		game()->player_dir = 0;
	else if (orientation == 'W')
		game()->player_dir = PI;
}
