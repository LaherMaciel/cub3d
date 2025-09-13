/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 15:47:56 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/09/12 18:07:16 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Copies the first string to the joined string buffer.
 *
 * This helper function copies characters from s1 to sjoin starting at
 * the current position indicated by i, and updates i to the new position.
 *
 * @param s1 The first string to copy.
 * @param sjoin The destination buffer for the joined string.
 * @param i Pointer to the current position in sjoin.
 * @return Pointer to the joined string buffer.
 */
char	*ft_copy_first_string(char *s1, char *sjoin, size_t *i)
{
	if (s1)
	{
		while (s1[*i] != '\0')
		{
			sjoin[*i] = s1[*i];
			*i += 1;
		}
	}
	return (sjoin);
}

/**
 * @brief Joins two strings with optional memory management.
 *
 * DIFFERENCE FROM ft_strjoin:
 * - This is an ENHANCED version with automatic memory management
 * - Accepts non-const char* parameters (can modify input strings)
 * - Includes a 'flag' parameter for automatic memory cleanup:
 *   - flag = 1: frees s1 after joining
 *   - flag = 2: frees s2 after joining  
 *   - flag = 3: frees both s1 and s2 after joining
 * - Handles NULL strings gracefully (returns empty string if both NULL)
 * - Uses ft_calloc instead of malloc for better memory safety
 * - Designed for projects requiring automatic memory management
 *
 * @param s1 The first string to join (can be freed if flag indicates).
 * @param s2 The second string to join (can be freed if flag indicates).
 * @param flag Memory management flag: 1=frees s1, 2=frees s2, 3=frees both.
 * @return New concatenated string, or empty string if both inputs are NULL.
 */
char	*ft_strjoin2(char *s1, char *s2, int flag)
{
	char	*sjoin;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (ft_strdup(""));
	sjoin = ft_calloc((ft_strlen(s1) + ft_strlen(s2)), sizeof(char) + 1);
	if (!sjoin)
		return (NULL);
	i = 0;
	if (s1)
	{
		sjoin = ft_copy_first_string(s1, sjoin, &i);
		if (flag == 1 || flag == 3)
			free(s1);
	}
	j = -1;
	if (s2)
	{
		while (s2[++j] != '\0')
			sjoin[i++] = s2[j];
		if (flag == 2 || flag == 3)
			free(s2);
	}
	return (sjoin);
}
