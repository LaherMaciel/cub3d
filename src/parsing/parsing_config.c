/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <lawences@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/01/19 17:12:09 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Attempts to parse texture configuration from a line
// Returns 1 if parsed, -1 on error, 0 if not a texture line
static int	parse_texture_config(char *line, int *config_count)
{
	int	result;

	result = parse_mandatory_textures(line, config_count);
	if (result == 1)
		return (1);
	if (result == -1)
		return (-1);
	return (0);
}

// Attempts to parse mandatory configuration (textures and colors)
// Returns 1 if parsed, -1 on error, 0 if not a config line
static int	parse_mandatory_config(char *line, int *config_count)
{
	int	result;

	result = parse_texture_config(line, config_count);
	if (result == 1)
		return (1);
	if (result == -1)
		return (-1);
	result = parse_color_config(line, config_count);
	if (result == 1)
		return (1);
	if (result == -1)
		return (-1);
	return (0);
}

// Processes a single configuration line
// Handles both mandatory and bonus configurations
// Returns 0 on success, 1 on error
static int	process_config_line(char *line, int *config_count)
{
	int	result;

	result = parse_mandatory_config(line, config_count);
	if (result == 1)
		return (0);
	if (result == -1)
		return (1);
	if (result == 0)
	{
		if (parse_bonus_config(line) != 0)
			return (1);
	}
	return (0);
}

// Processes all configuration lines until map is found
// Skips empty lines and validates configuration elements
// Returns 0 on success, 1 on error
static int	process_config_lines(char **lines, int *i, int *config_count)
{
	char	*trimmed;

	while (lines[*i])
	{
		if (ft_strlen(lines[*i]) == 0)
		{
			(*i)++;
			continue ;
		}
		trimmed = ft_strtrim(lines[*i], " \t\n");
		if (!trimmed || ft_strlen(trimmed) == 0)
		{
			free(trimmed);
			(*i)++;
			continue ;
		}
		free(trimmed);
		if (is_map_line(lines[*i]))
			break ;
		if (process_config_line(lines[*i], config_count) != 0)
			return (1);
		(*i)++;
	}
	return (0);
}

// Main configuration parsing function
// Validates that all 6 mandatory configuration elements are present
// Returns 0 on success, 1 on error
int	parse_configuration(char **lines, int *line_index)
{
	int	i;
	int	config_count;

	i = *line_index;
	config_count = 0;
	if (process_config_lines(lines, &i, &config_count) != 0)
		return (1);
	*line_index = i;
	if (config_count != 6)
	{
		ft_putstr_fd("Error: Missing configuration elements\n", 2);
		return (1);
	}
	return (0);
}
