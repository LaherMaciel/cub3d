/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalldigit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 09:24:29 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/01/19 09:33:44 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_isalldigit(char **array)
{
	int	i;
	int	j;

	i = -1;
	while (array[++i])
	{
		j = -1;
		while (array[i][++j])
			if (!ft_isdigit(array[i][j]) && !ft_isspace(array[i][j]))
				return (0);
	}
	return (1);
}
