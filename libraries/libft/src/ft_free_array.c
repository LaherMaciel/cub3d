/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:39:14 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/02/09 19:20:46 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Frees an array of strings and the array itself.
 *
 * This function frees each string in the array and then frees the array
 * pointer. If len is 0 or negative, it automatically calculates the array
 * length using ft_arraylen() by looking for a NULL terminator.
 *
 * @param array The array of strings to free.
 * @param len The length of the array (0 to auto-calculate).
 * @return NULL pointer.
 */
void	*ft_free_array(char **array, size_t len)
{
	size_t	i;

	i = 0;
	if (array)
	{
		if (len <= 0)
			len = ft_arraylen(array);
		while (i <= len)
			free(array[i++]);
		free(array);
	}
	return (NULL);
}

/**
 * @brief Frees a generic array of void pointers with a custom cleanup function.
 *
 * This function frees an array of void pointers by calling a custom cleanup
 * function for each element, then freeing the array itself.
 *
 * @param array The array of void pointers to free.
 * @param len The length of the array.
 * @param free_func A function pointer to the cleanup function for each element.
 * @return NULL pointer.
 */
void	*ft_free_array_void(void **array, size_t len, void (*free_func)(void *))
{
	size_t	i;

	i = 0;
	if (array)
	{
		while (i < len)
		{
			if (array[i] && free_func)
				free_func(array[i]);
			else if (array[i])
				free(array[i]);
			i++;
		}
		free(array);
	}
	return (NULL);
}

/**
 * @brief Frees a null-terminated array of void pointers with a custom cleanup
 * function.
 *
 * This function frees a null-terminated array of void pointers by calling a
 * custom cleanup function for each element until it encounters a NULL pointer.
 *
 * @param array The null-terminated array of void pointers to free.
 * @param free_func A function pointer to the cleanup function for each element.
 * @return NULL pointer.
 */
void	*ft_free_array_void_nullterm(void **array, void (*free_func)(void *))
{
	size_t	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			if (free_func)
				free_func(array[i]);
			else
				free(array[i]);
			i++;
		}
		free(array);
	}
	return (NULL);
}
