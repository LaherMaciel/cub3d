/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/09/13 02:37:15 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	ft_printf("Welcome to cub3d!\n");
	ft_printf("Window size: %dx%d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
	return (0);
}
