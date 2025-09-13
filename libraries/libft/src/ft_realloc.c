/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:38:04 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/23 12:39:56 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Reallocates memory with safety checks.
 *
 * This function reallocates memory by creating a new block of the specified
 * size, copying the old data to the new location, and freeing the original
 * pointer. If new_size is 0, it frees the original pointer and returns NULL.
 *
 * @param ptr Pointer to the existing memory block.
 * @param old_size Size of the existing memory block.
 * @param new_size New size to allocate.
 * @return Pointer to the reallocated memory, or NULL on failure.
 */
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (!new_size)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, old_size);
		free(ptr);
	}
	return (new_ptr);
}
