/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:18:25 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/15 13:55:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_map(char *filename)
{
	if (parse_cub_file(filename) != 0)
	{
		ft_printf("Error parsing map file\n");
		cleanup_parsing();
		close_program();
		exit(EXIT_FAILURE);
	}
	ft_printf("Map loaded successfully!\n");
	ft_printf("Map dimensions: %dx%d\n", game()->map_width, game()->map_height);
	ft_printf("Player position: (%.1f, %.1f) facing %c\n",
		game()->player_x, game()->player_y, game()->player_orientation);
}

void	convert_linked_list_to_array(t_map *head)
{
	t_map	*temp;
	int		i;
	int		map_size;

	map_size = ft_lstsize2(head);
	game()->map = malloc(sizeof(char *) * (map_size + 1));
	if (!game()->map)
	{
		ft_printf("Error: Memory allocation failed for map array\n");
		ft_lstclear2(&head, free);
		exit(EXIT_FAILURE);
	}
	temp = head;
	i = 0;
	while (temp && i < map_size)
	{
		game()->map[i] = temp->content;
		temp = temp->next;
		i++;
	}
	game()->map[i] = NULL;
	ft_printf("Map input:\n%t\n", game()->map);
}
