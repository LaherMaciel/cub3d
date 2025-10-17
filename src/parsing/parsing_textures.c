/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/17 12:53:47 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	parse_texture_line(char *line, char **texture_path)
{
	char	*path;
	int		start;

	start = 3;
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	path = ft_strdup(&line[start]);
	if (!path)
		return (1);
	path = ft_strtrim(path, " \t\n");
	if (ft_strlen(path) == 0)
		return (free(path), 1);
	*texture_path = path;
	return (0);
}

int	parse_north_south_textures(char *line, int *config_count)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (parse_texture_line(line, &game()->textures.no_path) != 0)
			return (ft_putstr_fd("Error\nInvalid north texture\n", 2), 1);
		(*config_count)++;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (parse_texture_line(line, &game()->textures.so_path) != 0)
			return (ft_putstr_fd("Error\nInvalid south texture\n", 2), 1);
		(*config_count)++;
	}
	else
		return (0);
	return (1);
}

int	parse_west_east_textures(char *line, int *config_count)
{
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (parse_texture_line(line, &game()->textures.we_path) != 0)
			return (ft_putstr_fd("Error\nInvalid west texture\n", 2), 1);
		(*config_count)++;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (parse_texture_line(line, &game()->textures.ea_path) != 0)
			return (ft_putstr_fd("Error\nInvalid east texture\n", 2), 1);
		(*config_count)++;
	}
	else
		return (0);
	return (1);
}

int	parse_bonus_config(char *line)
{
	if (ft_strncmp(line, "ROOF ", 5) == 0)
	{
		if (parse_texture_line(line, &game()->textures.roof_path) != 0)
			return (ft_putstr_fd("Error\nInvalid roof texture\n", 2), 1);
	}
	else if (ft_strncmp(line, "FLOOR ", 6) == 0)
	{
		if (parse_texture_line(line, &game()->textures.floor_path) != 0)
			return (ft_putstr_fd("Error\nInvalid floor texture\n", 2), 1);
	}
	else if (ft_strncmp(line, "WEAPON ", 7) == 0)
	{
		if (parse_texture_line(line, &game()->textures.weapon_path) != 0)
			return (ft_putstr_fd("Error\nInvalid weapon texture\n", 2), 1);
	}
	else
		return (ft_putstr_fd("Error\nUnknown configuration element\n", 2), 1);
	return (0);
}
