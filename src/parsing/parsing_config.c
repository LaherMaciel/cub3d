/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/17 12:53:47 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	parse_texture_config(char *line, int *config_count)
{
	if (parse_north_south_textures(line, config_count) == 1)
		return (1);
	if (parse_west_east_textures(line, config_count) == 1)
		return (1);
	return (0);
}

static int	parse_mandatory_config(char *line, int *config_count)
{
	if (parse_texture_config(line, config_count) == 1)
		return (1);
	if (parse_color_config(line, config_count) == 1)
		return (1);
	return (0);
}

static int	process_config_line(char *line, int *config_count)
{
	int	result;

	result = parse_mandatory_config(line, config_count);
	if (result == 1)
		return (0);
	else if (result == 0)
	{
		if (parse_bonus_config(line) != 0)
			return (1);
	}
	else
		return (result);
	return (0);
}

int	parse_configuration(char **lines, int *line_index)
{
	int	i;
	int	config_count;

	i = *line_index;
	config_count = 0;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) == 0
			|| ft_strlen(ft_strtrim(lines[i], " \t\n")) == 0)
		{
			i++;
			continue ;
		}
		if (is_map_line(lines[i]))
			break ;
		if (process_config_line(lines[i], &config_count) != 0)
			return (1);
		i++;
	}
	*line_index = i;
	if (config_count != 6)
		return (ft_putstr_fd("Error\nMissing configuration elements\n", 2), 1);
	return (0);
}
