/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/17 12:53:47 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	convert_rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

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

void	set_player_direction(char orientation)
{
	if (orientation == 'N')
		game()->player_dir = -M_PI / 2;
	else if (orientation == 'S')
		game()->player_dir = M_PI / 2;
	else if (orientation == 'E')
		game()->player_dir = 0;
	else if (orientation == 'W')
		game()->player_dir = M_PI;
}
