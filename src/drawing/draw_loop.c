/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 21:42:15 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/04 10:11:17 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
** Draw the entire minimap in the top-left corner
** Shows: walls (white), empty space (black), player (red with yellow line)
*/
void	draw_minimap(void)
{
	int	map_x;
	int	map_y;
	int	screen_x;
	int	screen_y;

	map_y = 0;
	while (map_y < game()->map_height)
	{
		map_x = 0;
		while (map_x < game()->map_width)
		{
			screen_x = START_X + (map_x * BLOCK);
			screen_y = START_Y + (map_y * BLOCK);
			if (game()->map[map_y][map_x] == '1')
				draw_minimap_square(screen_x, screen_y, BLOCK, COLOR_BLUE);
			else
				draw_minimap_square(screen_x, screen_y, BLOCK, COLOR_BLACK);
			map_x++;
		}
		map_y++;
	}
	draw_player_on_minimap();
}

int	draw_loop(void)
{
	clear_screen();
	move_player_2d(player());
	fov();
	draw_minimap();
	mlx_put_image_to_window(game()->mlx, game()->window, game()->image, 0, 0);
	return (0);
}
