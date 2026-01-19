/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_filled.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lawences <lawences@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 15:27:38 by lawences          #+#    #+#             */
/*   Updated: 2026/01/19 17:30:50 by lawences         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**fill_it(int x, int y, char **array)
{
	if (array[x][y] == '0')
	{
		array[x][y] = 'x';
	}
	else
	{
		array[x][y] = 'X';
		return (array);
	}
	if (array[x + 1][y] && !ft_strchr("1xX", array[x + 1][y]))
		array = fill_it(x + 1, y, array);
	if (array[x - 1][y] && !ft_strchr("1xX", array[x - 1][y]))
		array = fill_it(x - 1, y, array);
	if (array[x][y + 1] && !ft_strchr("1xX", array[x][y + 1]))
		array = fill_it(x, y + 1, array);
	if (array[x][y - 1] && !ft_strchr("1xX", array[x][y - 1]))
		array = fill_it(x, y - 1, array);
	return (array);
}

char	**ft_arraydup(char **org_array)
{
	char	**arraydup;
	int		i;

	arraydup = ft_calloc(ft_arraylen(org_array) + 1, sizeof(char *));
	if (!arraydup)
		return (NULL);
	i = -1;
	while (org_array[++i])
	{
		arraydup[i] = ft_strdup(org_array[i]);
		if (!arraydup[i])
		{
			ft_free_array(arraydup, i);
			return (NULL);
		}
	}
	return (arraydup);
}

int	find_player(int *x, int *y, char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				*x = i;
				*y = j;
				return (0);
			}
		}
	}
	return (1);
}

int	check_map_ok(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (!ft_strchr("10x", map[i][j]) && !ft_isspace(map[i][j]))
				return (1);
	}
	return (0);
}

int	flood_fill(void)
{
	char	**map;
	int		x;
	int		y;

	map = ft_arraydup(game()->map);
	if (!map)
		return (1);
	if (find_player(&x, &y, map))
		return (ft_free_array(map, ft_arraylen(map)), 1);
	map[x][y] = '0';
	map = fill_it(x, y, map);
	if (check_map_ok(map))
	{
		ft_putstr_fd("Error: Invalid Map\n", 2);
		return (ft_free_array(map, ft_arraylen(map)), 1);
	}
	return (ft_free_array(map, ft_arraylen(map)), 0);
}
