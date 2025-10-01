/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/01 21:37:58 by lahermaciel      ###   ########.fr       */
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
	mlx_loop(game()->mlx);
	return (0);
}
