/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 18:03:15 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/06/11 18:04:02 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Checks if a character is a whitespace character.
 *
 * This function checks if the given character is one of the standard
 * whitespace characters: space, tab, newline, vertical tab, form feed,
 * or carriage return.
 *
 * @param c The character to check.
 * @return Non-zero if the character is whitespace, 0 otherwise.
 */
int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}
