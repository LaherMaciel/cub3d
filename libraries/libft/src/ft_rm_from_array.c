/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rm_from_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:17:42 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/23 13:34:12 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Removes an element from an array of strings at a specified index.
 *
 * This function creates a new array without the element at the specified index.
 * It frees the removed element and the original array, then returns the new
 * array. If arraylen is 0, it automatically calculates the array length.
 *
 * @param array The original array of strings.
 * @param arraylen The length of the array (0 to auto-calculate).
 * @param index The index of the element to remove.
 * @return New array without the specified element, or NULL on failure.
 */
char	**ft_rm_from_array(char **array, size_t arraylen, size_t index)
{
	char	**new_array;
	size_t	i;
	size_t	j;

	if (!array)
		return (NULL);
	if (arraylen == 0)
		arraylen = ft_arraylen(array);
	new_array = ft_calloc(arraylen + 1, sizeof(char *));
	if (!new_array)
		return (NULL);
	i = 0;
	j = 0;
	while (i < arraylen)
	{
		if (i != index)
			new_array[j++] = array[i];
		i++;
	}
	if (array[index])
		free(array[index]);
	free(array);
	return (new_array);
}
