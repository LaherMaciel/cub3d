/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:00:21 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/15 13:55:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_lstdelone2(t_map *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}

void	ft_lstclear2(t_map **lst, void (*del)(void*))
{
	t_map	*temp;

	if (!*lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_lstdelone2(*lst, del);
		*lst = temp;
	}
	*lst = NULL;
}

t_map	*ft_lstnew2(void *content)
{
	t_map	*new_list;

	new_list = malloc(sizeof(t_map));
	if (!new_list)
		return (NULL);
	new_list->content = content;
	new_list->next = NULL;
	return (new_list);
}

t_map	*ft_lstlast2(t_map *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back2(t_map **lst, t_map *new)
{
	t_map	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast2(*lst);
	last->next = new;
}
