/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/01/14 22:41:43 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Moves player forward in the current direction
// Supports sprint mode (shift key)
static void	move_up(t_player *player)
{
	float	new_x;
	float	new_y;
	int		sprint;

	sprint = 1;
	if (player->key_shift)
		sprint = 2;
	new_x = game()->player_x + (MOVE_SPEED * sprint) * cos(game()->player_dir);
	new_y = game()->player_y + (MOVE_SPEED * sprint) * sin(game()->player_dir);
	move_to_new_x(new_x, new_y);
}

// Moves player backward (opposite of current direction)
// Supports sprint mode (shift key)
static void	move_down(t_player *player)
{
	float	new_x;
	float	new_y;
	int		sprint;

	sprint = 1;
	if (player->key_shift)
		sprint = 2;
	new_x = game()->player_x - (MOVE_SPEED * sprint) * cos(game()->player_dir);
	new_y = game()->player_y - (MOVE_SPEED * sprint) * sin(game()->player_dir);
	move_to_new_x(new_x, new_y);
}

// Moves player left (perpendicular to current direction)
// Supports sprint mode (shift key)
static void	move_left(t_player *player)
{
	float	new_x;
	float	new_y;
	int		sprint;

	sprint = 1;
	if (player->key_shift)
		sprint = 2;
	new_x = game()->player_x + (MOVE_SPEED * sprint) * cos(game()->player_dir
			- PI / 2);
	new_y = game()->player_y + (MOVE_SPEED * sprint) * sin(game()->player_dir
			- PI / 2);
	move_to_new_x(new_x, new_y);
}

// Moves player right (perpendicular to current direction)
// Supports sprint mode (shift key)
static void	move_right(t_player *player)
{
	float	new_x;
	float	new_y;
	int		sprint;

	sprint = 1;
	if (player->key_shift)
		sprint = 2;
	new_x = game()->player_x + (MOVE_SPEED * sprint) * cos(game()->player_dir
			+ PI / 2);
	new_y = game()->player_y + (MOVE_SPEED * sprint) * sin(game()->player_dir
			+ PI / 2);
	move_to_new_x(new_x, new_y);
}

// Main movement function - processes all player movement and rotation
// Called every frame in the game loop
void	move_player_2d(t_player *player)
{
	if (player->key_up)
		move_up(player);
	if (player->key_down)
		move_down(player);
	if (player->key_left)
		move_left(player);
	if (player->key_right)
		move_right(player);
	if (player->key_rot_left)
		game()->player_dir -= ROT_SPEED;
	if (player->key_rot_right)
		game()->player_dir += ROT_SPEED;
}
