/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 16:18:25 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/10 17:08:58 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	init_map(char *filename)
{
	int		fd;
	t_map	*head;
	t_map	*temp;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error opening map file: %s\n", strerror(errno));
		free(game()->window);
		free(game()->mlx);
		exit(EXIT_FAILURE);
	}
	head = NULL;
	line = get_next_line(fd);
	while (line)
	{
		temp = ft_lstnew2(line);
		if (!temp)
		{
			ft_printf("Error: Memory allocation failed\n");
			ft_lstclear2(&head, free);
			close(fd);
			exit(EXIT_FAILURE);
		}
		ft_lstadd_back2(&head, temp);
		line = get_next_line(fd);
	}
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
}
