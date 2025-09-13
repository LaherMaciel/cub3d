/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_and_clear.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:48:11 by marvin            #+#    #+#             */
/*   Updated: 2025/07/21 14:48:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Reallocates memory and initializes new space to zero.
 *
 * This function reallocates memory similar to ft_realloc(), but uses ft_calloc()
 * to initialize the new memory space to zero. It copies the old data to the
 * new location and frees the original pointer.
 *
 * @param ptr Pointer to the existing memory block.
 * @param old_size Size of the existing memory block.
 * @param new_size New size to allocate.
 * @return Pointer to the reallocated memory, or NULL on failure.
 */
void	*ft_realloc_and_clear(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (!new_size)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	new_ptr = ft_calloc(1, new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		ft_memcpy(new_ptr, ptr, old_size);
		free(ptr);
	}
	return (new_ptr);
}
