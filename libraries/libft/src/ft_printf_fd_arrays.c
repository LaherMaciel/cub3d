/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd_arrays.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 02:05:00 by lahermaciel      #+#    #+#             */
/*   Updated: 2025/09/13 02:05:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * @brief Prints an array of strings to a file descriptor, separated by spaces.
 *
 * This function takes a null-terminated array of strings and prints each
 * element to the specified file descriptor, separated by spaces. If the array
 * is NULL, it prints "(null)".
 *
 * @param fd The file descriptor to write to.
 * @param s   The null-terminated array of strings to print.
 *
 * @return The total number of characters written, or -1 on error.
 */
int	ft_fdprintargs(int fd, char **s)
{
	int	i;
	int	j;

	if (!s)
		return (ft_fdputstr(fd, "(null)"));
	i = 0;
	j = 0;
	while (s[j])
	{
		if (j > 0)
			i += ft_fdputchr(fd, ' ');
		i += ft_fdputstr(fd, s[j]);
		j++;
	}
	return (i);
}

/**
 * @brief Prints an array of strings to a file descriptor, separated by newlines.
 *
 * This function takes a null-terminated array of strings and prints each
 * element to the specified file descriptor, separated by newlines. If the array
 * is NULL, it prints "(null)".
 *
 * @param fd The file descriptor to write to.
 * @param s   The null-terminated array of strings to print.
 *
 * @return The total number of characters written, or -1 on error.
 */
int	ft_fdprintargsn(int fd, char **s)
{
	int	i;
	int	j;

	if (!s)
		return (ft_fdputstr(fd, "(null)"));
	i = 0;
	j = 0;
	while (s[j])
	{
		if (j > 0)
			i += ft_fdputchr(fd, '\n');
		i += ft_fdputstr(fd, s[j]);
		j++;
	}
	return (i);
}

/**
 * @brief Prints an array of strings to a file descriptor in quotes,
 * separated by spaces.
 *
 * This function takes a null-terminated array of strings and prints each
 * element to the specified file descriptor in quotes, separated by spaces. If
 * the array is NULL, it prints "(null)".
 *
 * @param fd The file descriptor to write to.
 * @param s   The null-terminated array of strings to print.
 *
 * @return The total number of characters written, or -1 on error.
 */
int	ft_fdprintargsc(int fd, char **s)
{
	int	i;
	int	j;

	if (!s)
		return (ft_fdputstr(fd, "(null)"));
	i = 0;
	j = 0;
	while (s[j])
	{
		if (j > 0)
			i += ft_fdputchr(fd, ' ');
		i += ft_fdputchr(fd, '"');
		i += ft_fdputstr(fd, s[j]);
		i += ft_fdputchr(fd, '"');
		j++;
	}
	return (i);
}

/**
 * @brief Prints an array of strings to a file descriptor in quotes,
 * separated by newlines.
 *
 * This function takes a null-terminated array of strings and prints each
 * element to the specified file descriptor in quotes, separated by newlines. If
 * the array is NULL, it prints "(null)".
 *
 * @param fd The file descriptor to write to.
 * @param s   The null-terminated array of strings to print.
 *
 * @return The total number of characters written, or -1 on error.
 */
int	ft_fdprintargscn(int fd, char **s)
{
	int	i;
	int	j;

	if (!s)
		return (ft_fdputstr(fd, "(null)"));
	i = 0;
	j = 0;
	while (s[j])
	{
		if (j > 0)
			i += ft_fdputchr(fd, '\n');
		i += ft_fdputchr(fd, '"');
		i += ft_fdputstr(fd, s[j]);
		i += ft_fdputchr(fd, '"');
		j++;
	}
	return (i);
}
