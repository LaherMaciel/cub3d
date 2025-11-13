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

// Sets up all MLX hooks: window events and main loop
void	setup_hooks(void)
{
	setup_window_hooks();
	mlx_loop_hook(game()->mlx, draw_loop, NULL);
}
