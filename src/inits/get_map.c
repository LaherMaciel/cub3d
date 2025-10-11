/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:18:25 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/11 14:54:18 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	read_map_lines(int fd, t_map **head)
{
	t_map	*temp;
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		temp = ft_lstnew2(line);
		if (!temp)
		{
			ft_printf("Error: Memory allocation failed\n");
			ft_lstclear2(head, free);
			close(fd);
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back2(head, temp);
		line = get_next_line(fd);
	}
}

void	init_map(char *filename)
{
	int		fd;
	t_map	*head;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error opening map file: %s\n", strerror(errno));
		free(game()->window);
		free(game()->mlx);
		exit(EXIT_FAILURE);
	}
	head = NULL;
	read_map_lines(fd, &head);
	close(fd);
	convert_linked_list_to_array(head);
	ft_lstclear2(&head, free);
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
