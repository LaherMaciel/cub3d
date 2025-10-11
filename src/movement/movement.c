/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:37:22 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/11 14:57:37 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	key_press(int keycode, t_player *player)
{
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	else if (keycode == KEY_W)
		player->key_up = true;
	else if (keycode == KEY_S)
		player->key_down = true;
	else if (keycode == KEY_A)
		player->key_left = true;
	else if (keycode == KEY_D)
		player->key_right = true;
	else if (keycode == KEY_LEFT)
		player->key_rot_left = true;
	else if (keycode == KEY_RIGHT)
		player->key_rot_right = true;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == KEY_ESC)
		exit(EXIT_SUCCESS);
	else if (keycode == KEY_W)
		player->key_up = false;
	else if (keycode == KEY_S)
		player->key_down = false;
	else if (keycode == KEY_A)
		player->key_left = false;
	else if (keycode == KEY_D)
		player->key_right = false;
	else if (keycode == KEY_LEFT)
		player->key_rot_left = false;
	else if (keycode == KEY_RIGHT)
		player->key_rot_right = false;
	return (0);
}

void	move_player_2d(t_player *player)
{
	if (player->key_up && (player->player_y > 10))
		player->player_y -= MOVE_SPEED;
	if (player->key_down && (player->player_y < game()->window_height - 20))
		player->player_y += MOVE_SPEED;
	if (player->key_left && (player->player_x > 10))
		player->player_x -= MOVE_SPEED;
	if (player->key_right && (player->player_x < game()->window_width - 20))
		player->player_x += MOVE_SPEED;
}

/* void	move_player_3d(t_player *player)
{
	if (player->key_up)
	{
		player->player_x += MOVE_SPEED * cos(player->player_dir);
		player->player_y += MOVE_SPEED * sin(player->player_dir);
	}
	if (player->key_down)
	{
		player->player_x -= MOVE_SPEED * cos(player->player_dir);
		player->player_y -= MOVE_SPEED * sin(player->player_dir);
	}
	if (player->key_left)
	{
		player->player_x += MOVE_SPEED * cos(player->player_dir - M_PI / 2);
		player->player_y += MOVE_SPEED * sin(player->player_dir - M_PI / 2);
	}
	if (player->key_right)
	{
		player->player_x += MOVE_SPEED * cos(player->player_dir + M_PI / 2);
		player->player_y += MOVE_SPEED * sin(player->player_dir + M_PI / 2);
	}
	if (player->key_rot_left)
		player->player_dir -= ROT_SPEED;
	if (player->key_rot_right)
		player->player_dir += ROT_SPEED;
} */
