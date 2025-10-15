/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:00:00 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/15 14:02:57 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	move_up(t_player *player, double move_speed)
{
	double	new_x;
	double	new_y;

	(void)player;
	new_x = game()->player_x + move_speed * cos(game()->player_dir);
	new_y = game()->player_y + move_speed * sin(game()->player_dir);
	if (is_valid_position(new_x, new_y))
	{
		game()->player_x = new_x;
		game()->player_y = new_y;
	}
}

static void	move_down(t_player *player, double move_speed)
{
	double	new_x;
	double	new_y;

	(void)player;
	new_x = game()->player_x - move_speed * cos(game()->player_dir);
	new_y = game()->player_y - move_speed * sin(game()->player_dir);
	if (is_valid_position(new_x, new_y))
	{
		game()->player_x = new_x;
		game()->player_y = new_y;
	}
}

static void	move_left(t_player *player, double move_speed)
{
	double	new_x;
	double	new_y;

	(void)player;
	new_x = game()->player_x + move_speed * cos(game()->player_dir
			- M_PI / 2);
	new_y = game()->player_y + move_speed * sin(game()->player_dir
			- M_PI / 2);
	if (is_valid_position(new_x, new_y))
	{
		game()->player_x = new_x;
		game()->player_y = new_y;
	}
}

static void	move_right(t_player *player, double move_speed)
{
	double	new_x;
	double	new_y;

	(void)player;
	new_x = game()->player_x + move_speed * cos(game()->player_dir
			+ M_PI / 2);
	new_y = game()->player_y + move_speed * sin(game()->player_dir
			+ M_PI / 2);
	if (is_valid_position(new_x, new_y))
	{
		game()->player_x = new_x;
		game()->player_y = new_y;
	}
}

void	move_player_2d(t_player *player)
{
	double	move_speed;

	move_speed = 0.1;
	if (player->key_up)
		move_up(player, move_speed);
	if (player->key_down)
		move_down(player, move_speed);
	if (player->key_left)
		move_left(player, move_speed);
	if (player->key_right)
		move_right(player, move_speed);
	if (player->key_rot_left)
		game()->player_dir -= ROT_SPEED;
	if (player->key_rot_right)
		game()->player_dir += ROT_SPEED;
}
