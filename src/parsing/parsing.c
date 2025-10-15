/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 21:33:16 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/15 14:18:53 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Initialize configuration with default values
static void	init_config(void)
{
	game()->textures.no_path = NULL;
	game()->textures.so_path = NULL;
	game()->textures.we_path = NULL;
	game()->textures.ea_path = NULL;
	game()->textures.roof_path = NULL;
	game()->textures.floor_path = NULL;
	game()->textures.weapon_path = NULL;
	game()->colors.floor_rgb = 0;
	game()->colors.ceiling_rgb = 0;
	game()->map = NULL;
	game()->map_width = 0;
	game()->map_height = 0;
	game()->player_x = 0.0;
	game()->player_y = 0.0;
	game()->player_orientation = '\0';
}

// Main parsing function
int	parse_cub_file(char *filename)
{
	int		fd;
	char	*line;
	char	**lines;
	int		line_count;
	int		i;

	init_config();
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nCannot open file\n", 2), 1);
	// Read all lines into array
	lines = NULL;
	line_count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!line)
			break;
		lines = ft_realloc(lines, line_count * sizeof(char*), (line_count + 1) * sizeof(char*));
		lines[line_count] = line;
		line_count++;
	}
	close(fd);
	if (!lines)
		return (ft_putstr_fd("Error\nEmpty file\n", 2), 1);
	// Parse configuration and map
	i = 0;
	if (parse_configuration(lines, &i) != 0)
		return (cleanup_parsing(), 1);
	if (parse_map(lines, i) != 0)
		return (cleanup_parsing(), 1);
	// Validate parsed data
	if (validate_map() != 0)
		return (cleanup_parsing(), 1);
	// Free lines array
	i = 0;
	while (i < line_count)
		free(lines[i++]);
	free(lines);
	return (0);
}

// Parse configuration elements (textures and colors)
int	parse_configuration(char **lines, int *line_index)
{
	int	i;
	int	config_count;

	i = *line_index;
	config_count = 0;
	while (lines[i])
	{
		// Skip empty lines
		if (ft_strlen(lines[i]) == 0 || ft_strlen(ft_strtrim(lines[i], " \t\n")) == 0)
		{
			i++;
			continue;
		}
		// Check if this is a map line
		if (is_map_line(lines[i]))
			break;
		// Parse texture lines
		if (ft_strncmp(lines[i], "NO ", 3) == 0)
		{
			if (parse_texture_line(lines[i], &game()->textures.no_path) != 0)
				return (ft_putstr_fd("Error\nInvalid north texture\n", 2), 1);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "SO ", 3) == 0)
		{
			if (parse_texture_line(lines[i], &game()->textures.so_path) != 0)
				return (ft_putstr_fd("Error\nInvalid south texture\n", 2), 1);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "WE ", 3) == 0)
		{
			if (parse_texture_line(lines[i], &game()->textures.we_path) != 0)
				return (ft_putstr_fd("Error\nInvalid west texture\n", 2), 1);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "EA ", 3) == 0)
		{
			if (parse_texture_line(lines[i], &game()->textures.ea_path) != 0)
				return (ft_putstr_fd("Error\nInvalid east texture\n", 2), 1);
			config_count++;
		}
		// Parse color lines
		else if (ft_strncmp(lines[i], "F ", 2) == 0)
		{
			if (parse_color_line(lines[i], &game()->colors.floor_rgb) != 0)
				return (ft_putstr_fd("Error\nInvalid floor color\n", 2), 1);
			config_count++;
		}
		else if (ft_strncmp(lines[i], "C ", 2) == 0)
		{
			if (parse_color_line(lines[i], &game()->colors.ceiling_rgb) != 0)
				return (ft_putstr_fd("Error\nInvalid ceiling color\n", 2), 1);
			config_count++;
		}
		// Parse bonus texture lines
		else if (ft_strncmp(lines[i], "ROOF ", 5) == 0)
		{
			if (parse_texture_line(lines[i], &game()->textures.roof_path) != 0)
				return (ft_putstr_fd("Error\nInvalid roof texture\n", 2), 1);
		}
		else if (ft_strncmp(lines[i], "FLOOR ", 6) == 0)
		{
			if (parse_texture_line(lines[i], &game()->textures.floor_path) != 0)
				return (ft_putstr_fd("Error\nInvalid floor texture\n", 2), 1);
		}
		else if (ft_strncmp(lines[i], "WEAPON ", 7) == 0)
		{
			if (parse_texture_line(lines[i], &game()->textures.weapon_path) != 0)
				return (ft_putstr_fd("Error\nInvalid weapon texture\n", 2), 1);
		}
		else
			return (ft_putstr_fd("Error\nUnknown configuration element\n", 2), 1);
		i++;
	}
	*line_index = i;
	if (config_count != 6)
		return (ft_putstr_fd("Error\nMissing configuration elements\n", 2), 1);
	return (0);
}

// Parse texture line (e.g., "NO ./path/to/texture")
int	parse_texture_line(char *line, char **texture_path)
{
	char	*path;
	int		start;

	start = 3; // Skip "NO "
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	path = ft_strdup(&line[start]);
	if (!path)
		return (1);
	// Remove trailing whitespace and newline
	path = ft_strtrim(path, " \t\n");
	if (ft_strlen(path) == 0)
		return (free(path), 1);
	*texture_path = path;
	return (0);
}

// Parse color line (e.g., "F 220,100,0")
int	parse_color_line(char *line, int *color)
{
	char	**rgb_values;
	int		r, g, b;
	int		start;

	start = 2; // Skip "F "
	while (line[start] == ' ' || line[start] == '\t')
		start++;
	rgb_values = ft_split(&line[start], ',');
	if (!rgb_values || ft_arraylen(rgb_values) != 3)
		return (ft_putstr_fd("Error\nInvalid color format\n", 2), 1);
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (ft_putstr_fd("Error\nColor values must be between 0-255\n", 2), 1);
	*color = convert_rgb_to_int(r, g, b);
	ft_free_array(rgb_values, 3);
	return (0);
}

// Convert RGB values to integer
int	convert_rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

// Check if line is a map line (contains only 0, 1, N, S, E, W, spaces)
bool	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != 'N' && 
			line[i] != 'S' && line[i] != 'E' && line[i] != 'W' && 
			line[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

// Parse map section
int	parse_map(char **lines, int line_index)
{
	int	map_height;

	// Skip empty lines before map
	while (lines[line_index] && 
		   (ft_strlen(lines[line_index]) == 0 || 
			ft_strlen(ft_strtrim(lines[line_index], " \t\n")) == 0))
		line_index++;
	if (!lines[line_index])
		return (ft_putstr_fd("Error\nNo map found\n", 2), 1);
	// Count map lines
	map_height = count_map_lines(lines, line_index);
	if (map_height == 0)
		return (ft_putstr_fd("Error\nEmpty map\n", 2), 1);
	game()->map_height = map_height;
	// Allocate and extract map
	game()->map = ft_calloc(map_height + 1, sizeof(char*));
	if (!game()->map)
		return (ft_putstr_fd("Error\nMemory allocation failed\n", 2), 1);
	extract_map(lines, line_index, map_height);
	return (0);
}

// Count valid map lines
int	count_map_lines(char **lines, int start_index)
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

// Extract map lines into 2D array
void	extract_map(char **lines, int start_index, int map_height)
{
	int		i;
	int		j;
	int		max_width;
	max_width = 0;
	i = 0;
	while (i < map_height)
	{
		game()->map[i] = ft_strdup(lines[start_index + i]);
		if (!game()->map[i])
			return;
		if (game()->map[i][ft_strlen(game()->map[i]) - 1] == '\n')
			game()->map[i][ft_strlen(game()->map[i]) - 1] = '\0';
		// Find maximum width
		if ((int)ft_strlen(game()->map[i]) > max_width)
			max_width = ft_strlen(game()->map[i]);
		i++;
	}
	game()->map_width = max_width;
	// Pad shorter lines with spaces to make rectangular
	i = 0;
	while (i < map_height)
	{
		if ((int)ft_strlen(game()->map[i]) < max_width)
		{
			j = ft_strlen(game()->map[i]);
			while (j < max_width)
			{
				char	*temp;

				temp = ft_strjoin(game()->map[i], " ");
				free(game()->map[i]);
				game()->map[i] = temp;
				j++;
			}
		}
		i++;
	}
}

// Validate the parsed map
int	validate_map(void)
{
	if (validate_map_closed() != 0)
		return (1);
	if (validate_player_position() != 0)
		return (1);
	return (0);
}

// Validate that map is closed (surrounded by walls)
int	validate_map_closed(void)
{
	int	i;
	int	j;

	// Check top and bottom borders
	i = 0;
	while (i < game()->map_width)
	{
		if (game()->map[0][i] != '1' && game()->map[0][i] != ' ')
			return (ft_putstr_fd("Error\nMap not closed at top\n", 2), 1);
		if (game()->map[game()->map_height - 1][i] != '1' && 
			game()->map[game()->map_height - 1][i] != ' ')
			return (ft_putstr_fd("Error\nMap not closed at bottom\n", 2), 1);
		i++;
	}
	// Check left and right borders
	i = 0;
	while (i < game()->map_height)
	{
		if (game()->map[i][0] != '1' && game()->map[i][0] != ' ')
			return (ft_putstr_fd("Error\nMap not closed at left\n", 2), 1);
		if (game()->map[i][game()->map_width - 1] != '1' && 
			game()->map[i][game()->map_width - 1] != ' ')
			return (ft_putstr_fd("Error\nMap not closed at right\n", 2), 1);
		i++;
	}
	// Check for isolated spaces inside the map
	i = 1;
	while (i < game()->map_height - 1)
	{
		j = 1;
		while (j < game()->map_width - 1)
		{
			if (game()->map[i][j] == '0' || ft_strchr("NSEW", game()->map[i][j]))
			{
				// Check if surrounded by walls or spaces
				if (game()->map[i-1][j] == ' ' || game()->map[i+1][j] == ' ' ||
					game()->map[i][j-1] == ' ' || game()->map[i][j+1] == ' ')
					return (ft_putstr_fd("Error\nMap not properly closed\n", 2), 1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

// Validate player position (exactly one player, valid orientation)
int	validate_player_position(void)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < game()->map_height)
	{
		j = 0;
		while (j < game()->map_width)
		{
			if (ft_strchr("NSEW", game()->map[i][j]))
			{
				player_count++;
				if (player_count > 1)
					return (ft_putstr_fd("Error\nMultiple player positions\n", 2), 1);
				game()->player_x = j + 0.5;
				game()->player_y = i + 0.5;
				game()->player_orientation = game()->map[i][j];
				// Set initial direction based on orientation
				if (game()->map[i][j] == 'N')
					game()->player_dir = -M_PI / 2;
				else if (game()->map[i][j] == 'S')
					game()->player_dir = M_PI / 2;
				else if (game()->map[i][j] == 'E')
					game()->player_dir = 0;
				else if (game()->map[i][j] == 'W')
					game()->player_dir = M_PI;
				// Replace player character with '0'
				game()->map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	if (player_count == 0)
		return (ft_putstr_fd("Error\nNo player position found\n", 2), 1);
	return (0);
}

// Cleanup allocated memory
void	cleanup_parsing(void)
{
	if (game()->textures.no_path)
		free(game()->textures.no_path);
	if (game()->textures.so_path)
		free(game()->textures.so_path);
	if (game()->textures.we_path)
		free(game()->textures.we_path);
	if (game()->textures.ea_path)
		free(game()->textures.ea_path);
	if (game()->textures.roof_path)
		free(game()->textures.roof_path);
	if (game()->textures.floor_path)
		free(game()->textures.floor_path);
	if (game()->textures.weapon_path)
		free(game()->textures.weapon_path);
	if (game()->map)
	{
		int i = 0;
		while (i < game()->map_height)
		{
			if (game()->map[i])
				free(game()->map[i]);
			i++;
		}
		free(game()->map);
	}
}