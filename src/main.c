/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/01 11:10:12 by karocha-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_player	*player(void)
{
	static t_player	player;

	return (&player);
}

t_game	*game(void)
{
	static t_game	game;

	return (&game);
}

int	main(void)
{
	init_game();
	init_player();
	setup_hooks();
	draw_square(player()->player_x, player()->player_y, 10);
	mlx_loop(game()->mlx);
	return (0);
}
