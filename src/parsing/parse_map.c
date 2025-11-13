/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/13 14:31:20 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Counts consecutive map lines starting from start_index
static int	count_map_lines(char **lines, int start_index)
{
	int	count;
	int	i;

	count = 0;
	i = start_index;
	while (lines[i] && is_map_line(lines[i]))
	{
		count++;
		i++;
	}
	return (count);
}

// Pads a map line with spaces to match max_width
static int	pad_map_line(int i, int max_width)
{
	int		j;
	char	space;
	char	space_str[2];
	char	*temp;

	space = ' ';
	j = ft_strlen(game()->map[i]);
	while (j < max_width)
	{
		space_str[0] = space;
		space_str[1] = '\0';
		temp = ft_strjoin(game()->map[i], space_str);
		free(game()->map[i]);
		game()->map[i] = temp;
		j++;
	}
	return (0);
}

// Extracts map lines from the file and pads them to uniform width
static void	extract_map_lines(char **lines, int start_index, int map_height)
{
	int		i;
	int		max_width;

	max_width = 0;
	i = 0;
	while (i < map_height)
	{
		game()->map[i] = ft_strdup(lines[start_index + i]);
		if (!game()->map[i])
			return ;
		if (game()->map[i][ft_strlen(game()->map[i]) - 1] == '\n')
			game()->map[i][ft_strlen(game()->map[i]) - 1] = '\0';
		if ((int)ft_strlen(game()->map[i]) > max_width)
			max_width = ft_strlen(game()->map[i]);
		i++;
	}
	game()->map_width = max_width;
	i = 0;
	while (i < map_height)
	{
		if ((int)ft_strlen(game()->map[i]) < max_width)
			pad_map_line(i, max_width);
		i++;
	}
}

// Finds the first non-empty line that marks the start of the map
static int	find_map_start(char **lines, int line_index)
{
	char	*trimmed;

	while (lines[line_index])
	{
		if (ft_strlen(lines[line_index]) == 0)
		{
			line_index++;
			continue ;
		}
		trimmed = ft_strtrim(lines[line_index], " \t\n");
		if (!trimmed || ft_strlen(trimmed) == 0)
		{
			free(trimmed);
			line_index++;
			continue ;
		}
		free(trimmed);
		break ;
	}
	return (line_index);
}

// Main map parsing function
// Extracts and validates the map section from the file
// Returns 0 on success, 1 on error
int	parse_map(char **lines, int line_index)
{
	int	map_height;

	line_index = find_map_start(lines, line_index);
	if (!lines[line_index])
		return (ft_putstr_fd("Error: No map found\n", 2), 1);
	map_height = count_map_lines(lines, line_index);
	if (map_height == 0)
		return (ft_putstr_fd("Error: Empty map\n", 2), 1);
	game()->map_height = map_height;
	game()->map = ft_calloc(map_height + 1, sizeof (char *));
	if (!game()->map)
		return (ft_putstr_fd("Error: Memory allocation failed\n", 2), 1);
	extract_map_lines(lines, line_index, map_height);
	return (0);
}
