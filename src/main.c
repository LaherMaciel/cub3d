/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/13 14:33:48 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <signal.h>

// Returns a pointer to the singleton player instance
t_player	*player(void)
{
	static t_player	player;

	return (&player);
}

// Returns a pointer to the singleton game instance
t_game	*game(void)
{
	static t_game	game;

	return (&game);
}

// Main entry point of the program
// Validates arguments, initializes game, and starts the main loop
int	main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_putstr_fd("Error: Invalid number of arguments\n", 2), 1);
	if (ft_strlen(argv[1]) < 5
		|| ft_strlen(ft_strnstr(argv[1], ".cub", 0)) != 4)
		return (ft_putstr_fd("Error: Invalid file extension\n", 2), 1);
	ft_printf("Starting Cub3D...\n");
	init_game();
	init_map(argv[1]);
	init_player();
	setup_hooks();
	mlx_loop(game()->mlx);
	return (0);
}
