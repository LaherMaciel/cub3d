/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:27:48 by karocha-          #+#    #+#             */
/*   Updated: 2025/10/02 00:31:00 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	close_game(void)
{
	if (game() == NULL)
		exit(EXIT_SUCCESS);
	if (game()->image)
		mlx_destroy_image(game()->mlx, game()->image);
	if (game()->window)
		mlx_destroy_window(game()->mlx, game()->window);
	if (game()->mlx)
	{
		mlx_destroy_display(game()->mlx);
		free(game()->mlx);
	}
	exit(EXIT_SUCCESS);
}

int	close_program(void)
{
	close_game();
	return (0);
}
