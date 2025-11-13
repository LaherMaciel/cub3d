/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 13:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/17 13:29:30 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Sets up MLX window event hooks
// Handles window close, key press, and key release events
void	setup_window_hooks(void)
{
	mlx_hook(game()->window, 17, 0, close_program, NULL);
	mlx_hook(game()->window, 2, 1L << 0, (int (*)())key_press, player());
	mlx_hook(game()->window, 3, 1L << 1, (int (*)())key_release, player());
}
