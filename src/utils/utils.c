/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 10:27:48 by karocha-          #+#    #+#             */
/*   Updated: 2025/10/01 11:14:25 by karocha-         ###   ########.fr       */
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

int	close_program(void *param)
{
	(void)param;
	close_game();
	return (0);
}

void	setup_hooks(void)
{
	mlx_hook(game()->window, 17, 0, close_program, NULL);
	mlx_hook(game()->window, 2, 1L << 0, key_press, player());
	mlx_hook(game()->window, 3, 1L << 1, key_release, player());
	mlx_loop_hook(game()->mlx, draw_loop, NULL);
}
