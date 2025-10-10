/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 21:42:15 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/01 22:27:28 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	draw_loop(void)
{
	clear_screen();
	move_player_2d(player());
	draw_circle(player()->player_x, player()->player_y, 10);
	mlx_put_image_to_window(game()->mlx, game()->window, game()->image, 0, 0);
	return (0);
}
