/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 21:18:44 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/08/11 12:03:42 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Swaps two string pointers with optional memory management.
 *
 * This function swaps the values of two string pointers. If flag is 1, it
 * creates new copies of the strings using ft_strdup() and frees the original
 * pointers. If flag is 0, it simply swaps the pointers without creating copies
 * or freeing memory.
 *
 * @param a Pointer to the first string pointer.
 * @param b Pointer to the second string pointer.
 * @param flag If 1, creates copies and frees originals; if 0, just swaps
 * pointers.
 */
void	ft_swap(char **a, char **b, int flag)
{
	char	*temp;

	temp = *a;
	if (flag)
	{
		*a = ft_strdup(*b);
		free(*b);
		*b = ft_strdup(temp);
		free(temp);
	}
	else
	{
		*a = *b;
		*b = temp;
	}
}
