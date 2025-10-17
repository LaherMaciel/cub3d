/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/17 12:53:34 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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

int	parse_map(char **lines, int line_index)
{
	int	map_height;

	while (lines[line_index]
		&& (ft_strlen(lines[line_index]) == 0
			|| ft_strlen(ft_strtrim(lines[line_index], " \t\n")) == 0))
		line_index++;
	if (!lines[line_index])
		return (ft_putstr_fd("Error\nNo map found\n", 2), 1);
	map_height = count_map_lines(lines, line_index);
	if (map_height == 0)
		return (ft_putstr_fd("Error\nEmpty map\n", 2), 1);
	game()->map_height = map_height;
	game()->map = ft_calloc(map_height + 1, sizeof (char *));
	if (!game()->map)
		return (ft_putstr_fd("Error\nMemory allocation failed\n", 2), 1);
	extract_map_lines(lines, line_index, map_height);
	return (0);
}
