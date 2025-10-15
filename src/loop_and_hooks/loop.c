/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 21:38:43 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/15 13:04:29 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	setup_hooks(void)
{
	mlx_hook(game()->window, 17, 0, close_program, NULL);
	mlx_hook(game()->window, 2, 1L << 0, (int (*)())key_press, player());
	mlx_hook(game()->window, 3, 1L << 1, (int (*)())key_release, player());
	mlx_loop_hook(game()->mlx, draw_loop, NULL);
}
