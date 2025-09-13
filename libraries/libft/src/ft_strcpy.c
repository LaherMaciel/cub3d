/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:31:01 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/05/19 17:41:27 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Copies a string from source to destination.
 *
 * This function copies characters from src to dest until it encounters
 * a null terminator. It does not add a null terminator to dest, so
 * dest must be large enough to hold the entire string plus null terminator.
 * If src is NULL, the function returns dest without modification.
 *
 * @param dest The destination string buffer (must be large enough).
 * @param src The source string to copy (can be NULL).
 * @return Pointer to the destination string.
 */
char	*ft_strcpy(char *dest, char *src)
{
	size_t	i;

	i = -1;
	if (src)
	{
		while (src[++i])
			dest[i] = src[i];
	}
	return (dest);
}
