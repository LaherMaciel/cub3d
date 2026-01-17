/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/13 14:41:36 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Reads all lines from a file and stores them in a dynamically allocated array
// Returns 0 on success, 1 on error
static int	read_file_lines(char *filename, char ***lines, int *line_count)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	*lines = NULL;
	*line_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		*lines = ft_realloc(*lines, *line_count * sizeof(char *),
				(*line_count + 2) * sizeof(char*));
		(*lines)[*line_count] = line;
		(*line_count)++;
		(*lines)[*line_count] = NULL;
		line = get_next_line(fd);
	}
	close(fd);
	if (!*lines)
		return (1);
	(*lines)[*line_count] = NULL;
	return (0);
}

// Frees the lines array and exits the program with error code
// Used for cleanup when parsing errors occur
static void	free_and_exit_on_error(char **lines, int line_count)
{
	int	j;

	j = 0;
	while (j < line_count)
		free(lines[j++]);
	free(lines);
	error_exit(NULL, 1);
}

// Validates that there is no non-empty content after the map section
// Returns 0 if valid, 1 if invalid content found
static int	validate_no_content_after_map(char **lines, int i, int line_count)
{
	char	*trimmed;

	while (lines[i] && is_map_line(lines[i]))
		i++;
	while (lines[i])
	{
		if (ft_strlen(lines[i]) > 0)
		{
			trimmed = ft_strtrim(lines[i], " \t\n");
			if (trimmed && ft_strlen(trimmed) > 0)
			{
				free(trimmed);
				ft_putstr_fd("Error: Content found after map\n", 2);
				free_and_exit_on_error(lines, line_count);
			}
			free(trimmed);
		}
		i++;
	}
	return (0);
}

// Parses configuration, map, and validates the entire file content
// Returns 0 on success, 1 on error
static int	parse_file_content(char **lines, int line_count)
{
	int	i;

	i = 0;
	if (parse_configuration(lines, &i) != 0 || parse_map(lines, i) != 0
		|| validate_map() != 0)
		free_and_exit_on_error(lines, line_count);
	if (validate_no_content_after_map(lines, i, line_count) != 0)
		return (1);
	return (0);
}

// Main parsing function: reads and parses a .cub file
// Validates configuration, map, and file structure
// Returns 0 on success, 1 on error
int	parse_cub_file(char *filename)
{
	char	**lines;
	int		line_count;
	int		j;

	init_config_parsing();
	if (read_file_lines(filename, &lines, &line_count) != 0)
	{
		ft_putstr_fd("Error while trying to read the map\n", 2);
		error_exit(NULL, 1);
	}
	if (parse_file_content(lines, line_count) != 0)
		return (1);
	j = 0;
	while (j < line_count)
		free(lines[j++]);
	free(lines);
	return (0);
}
