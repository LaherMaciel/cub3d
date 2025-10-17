/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/17 13:19:50 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	read_file_lines(char *filename, char ***lines, int *line_count)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nCannot open file\n", 2), 1);
	*lines = NULL;
	*line_count = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		*lines = ft_realloc(*lines, *line_count * sizeof(char *),
				(*line_count + 1) * sizeof (char*));
		(*lines)[*line_count] = line;
		(*line_count)++;
		line = get_next_line(fd);
	}
	close(fd);
	if (!*lines)
		return (ft_putstr_fd("Error\nEmpty file\n", 2), 1);
	return (0);
}

static void	free_lines(char **lines, int line_count)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

int	parse_cub_file(char *filename)
{
	char	**lines;
	int		line_count;
	int		i;

	init_config_parsing();
	if (read_file_lines(filename, &lines, &line_count) != 0)
		return (1);
	i = 0;
	if (parse_configuration(lines, &i) != 0)
		return (cleanup_parsing(), free_lines(lines, line_count), 1);
	if (parse_map(lines, i) != 0)
		return (cleanup_parsing(), free_lines(lines, line_count), 1);
	if (validate_map() != 0)
		return (cleanup_parsing(), free_lines(lines, line_count), 1);
	free_lines(lines, line_count);
	return (0);
}
