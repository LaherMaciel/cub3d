/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 21:42:15 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/03 23:07:52 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	draw_loop(void)
{
	clear_screen();
	move_player_2d(player());
	//draw_map_2d();
	fov();
	mlx_put_image_to_window(game()->mlx, game()->window, game()->image, 0, 0);
	return (0);
}
