/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraylen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwencesl <lwencesl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 19:35:50 by lwencesl          #+#    #+#             */
/*   Updated: 2023/06/20 16:12:22 by lwencesl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Calculates the length of a null-terminated array of pointers.
 *
 * This function calculates the length of a null-terminated array of pointers by
 * iterating through its elements until a NULL pointer is encountered. It counts
 * the number of valid pointers before the NULL terminator.
 *
 * @param a The null-terminated array of pointers whose length is to be
 * calculated.
 * @return The length of the array (number of valid pointers before NULL).
 */
size_t	ft_arraylen(char **a)
{
	size_t	i;

	if (!a)
		return (0);
	i = 0;
	while (a[i])
		i++;
	return (i);
}

/**
 * @brief Calculates the length of a null-terminated array of void pointers.
 *
 * This function calculates the length of a null-terminated array of void
 * pointers by iterating through its elements until a NULL pointer is
 * encountered. It counts the number of valid pointers before the NULL
 * terminator.
 *
 * @param array The null-terminated array of void pointers.
 * @return The length of the array (number of valid pointers before NULL).
 */
size_t	ft_arraylen_void_nullterm(void **array)
{
	size_t	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		i++;
	return (i);
}
