/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/13 14:31:20 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Checks if the file path has a .xpm extension
static int	has_xpm_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	return (ft_strncmp(&path[len - 4], ".xpm", 4) == 0);
}

// Validates that the texture path is not empty and has .xpm extension
// Prints error message if validation fails
static int	validate_texture_path(char *trimmed, char *texture_name)
{
	if (ft_strlen(trimmed) == 0)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(texture_name, 2);
		ft_putstr_fd(" texture path is empty\n", 2);
		return (1);
	}
	if (!has_xpm_extension(trimmed))
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(texture_name, 2);
		ft_putstr_fd(" texture file must have .xpm extension\n", 2);
		return (1);
	}
	return (0);
}

// Parses a texture line (NO, SO, WE, EA) and extracts the texture path
// Returns 0 on success, 1 on error
int	parse_texture_line(char *line, char **texture_path, char *texture_name)
{
	char	*path;
	char	*trimmed;
	int		start;

	start = 3;
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	path = ft_strdup(&line[start]);
	if (!path)
		return (1);
	trimmed = ft_strtrim(path, " \t\n");
	free(path);
	if (!trimmed)
		return (1);
	if (validate_texture_path(trimmed, texture_name) != 0)
	{
		free(trimmed);
		return (1);
	}
	*texture_path = trimmed;
	return (0);
}

// Parses mandatory texture configuration lines (NO, SO, WE, EA)
// Increments config_count on successful parsing
// Returns 1 if parsed successfully, -1 on error, 0 if not a texture line
int	parse_mandatory_textures(char *line, int *config_count)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && parse_texture_line(line,
			&game()->textures.no_path, "North") == 0)
		return ((*config_count)++, 1);
	if (ft_strncmp(line, "SO ", 3) == 0 && parse_texture_line(line,
			&game()->textures.so_path, "South") == 0)
		return ((*config_count)++, 1);
	if (ft_strncmp(line, "WE ", 3) == 0 && parse_texture_line(line,
			&game()->textures.we_path, "West") == 0)
		return ((*config_count)++, 1);
	if (ft_strncmp(line, "EA ", 3) == 0 && parse_texture_line(line,
			&game()->textures.ea_path, "East") == 0)
		return ((*config_count)++, 1);
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
		return (-1);
	return (0);
}

// Parses bonus texture configuration lines (ROOF, FLOOR)
// Returns 0 on success, 1 on error
int	parse_bonus_config(char *line)
{
	if (ft_strncmp(line, "ROOF ", 5) == 0)
	{
		if (parse_texture_line(line, &game()->textures.roof_path, "Roof") != 0)
			return (1);
	}
	else if (ft_strncmp(line, "FLOOR ", 6) == 0)
	{
		if (parse_texture_line(line, &game()->textures.floor_path,
				"Floor") != 0)
			return (1);
	}
	else
	{
		ft_putstr_fd("Error: Unknown configuration element\n", 2);
		return (1);
	}
	return (0);
}
