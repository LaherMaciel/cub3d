/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 23:05:35 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/01/14 23:05:49 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	error_exit(char *message, int code)
{
	if (message != NULL && ft_strlen(message) > 0)
		ft_putstr_fd(message, 2);
	free_all();
	if (game()->image && game()->mlx)
		mlx_destroy_image(game()->mlx, game()->image);
	if (game()->window && game()->mlx)
		mlx_destroy_window(game()->mlx, game()->window);
	if (game()->mlx)
	{
		mlx_destroy_display(game()->mlx);
		free(game()->mlx);
	}
	exit(code);
}
