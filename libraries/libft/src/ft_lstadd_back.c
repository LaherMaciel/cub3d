/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwencesl <lwencesl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:53:57 by lwencesl          #+#    #+#             */
/*   Updated: 2023/06/22 15:35:10 by lwencesl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Adds a new element to the end of a linked list.
 *
 * This function adds the given 'new' element to the end of the linked list
 * pointed to by 'lst'. If the 'lst' pointer is NULL, the 'lst' pointer will be
 * updated to point to the 'new' element.
 *
 * @param lst A pointer to a pointer to the first element of the linked list.
 * @param new The element to be added to the end of the linked list.
 */
void	ft_lstadd_back(t_list **lst, t_list *new_node)
{
	t_list	*temp;

	if (!new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new_node;
}
