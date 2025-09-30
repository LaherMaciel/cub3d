/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/09/30 21:32:58 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(void)
{
	t_game		game;
	t_player	player;

	init_game(&game);
	init_player(&player);
	draw_square(&game, player.player_x, player.player_y, 10);
	mlx_loop(game.mlx);
	return (0);
}
