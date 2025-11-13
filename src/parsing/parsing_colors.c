/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/13 14:33:48 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Parses a color line (F or C) and extracts RGB values
// Validates RGB values are between 0-255
// Returns 0 on success, 1 on error
static int	parse_color_line(char *line, int *color)
{
	char	**rgb_values;
	int		r;
	int		g;
	int		b;
	int		start;

	start = 2;
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	rgb_values = ft_split(&line[start], ',');
	if (!rgb_values || ft_arraylen(rgb_values) != 3)
		return (ft_putstr_fd("Error: Invalid color format\n", 2), 1);
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0
		|| b > 255)
		return (ft_putstr_fd("Error: Color values "
				"must be between 0-255\n", 2), 1);
	*color = convert_rgb_to_int(r, g, b);
	ft_free_array(rgb_values, 3);
	return (0);
}

// Parses floor (F) or ceiling (C) color configuration
// Increments config_count on successful parsing
// Returns 1 if parsed successfully, -1 on error, 0 if not a color line
int	parse_color_config(char *line, int *config_count)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (parse_color_line(line, &game()->colors.floor_rgb) != 0)
			return (-1);
		(*config_count)++;
		return (1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (parse_color_line(line, &game()->colors.ceiling_rgb) != 0)
			return (-1);
		(*config_count)++;
		return (1);
	}
	return (0);
}
