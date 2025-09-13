/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwencesl <lwencesl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:37:51 by lwencesl          #+#    #+#             */
/*   Updated: 2022/11/15 15:43:42 by lwencesl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static size_t	ft_count_digits_integer(long int n)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		n = n * (-1);
		i++;
	}
	if (n <= 9)
		i++;
	else
		i = i + 1 + ft_count_digits_integer(n / 10);
	return (i);
}

static char	*ft_write_integer_to_string(long int n, char *ito, size_t size)
{
	if (n < 0)
	{
		ito[0] = '-';
		if (n <= -2147483648)
		{
			ito[1] = '2';
			n = -147483648;
		}
		n = n * (-1);
	}
	if (n <= 9)
		ito[size] = n + 48;
	else
	{
		ito[size] = n % 10 + 48;
		ito = ft_write_integer_to_string(n / 10, ito, size - 1);
	}
	return (ito);
}

/**
 * @brief Converts an integer to a null-terminated string representation.
 *
 * This function converts the integer 'n' into a string representation and
 * returns a dynamically allocated null-terminated character array (string)
 * containing the result. The memory for the string is allocated using malloc.
 * Make sure to free the memory using free() when the string is no longer
 * needed.
 *
 * @param n The integer value to be converted to a string.
 * @return A pointer to the allocated string representing the integer, or NULL
 * if allocation fails.
 */
char	*ft_itoa(int n)
{
	size_t		size;
	char		*str;

	size = ft_count_digits_integer(n);
	str = (char *) ft_calloc((size + 1), sizeof(char));
	if (!str)
		return (NULL);
	str = ft_write_integer_to_string(n, str, size - 1);
	return (str);
}
