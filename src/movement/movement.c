/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:37:22 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/01/09 22:37:05 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

// Handles key press events
// Sets corresponding player key flags to true
// Returns 0 on success
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
	else if (keycode == KEY_SHIFT)
		player->key_shift = true;
	return (0);
}

// Handles key release events
// Sets corresponding player key flags to false
// Returns 0 on success
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
	else if (keycode == KEY_SHIFT)
		player->key_shift = false;
	return (0);
}

// Checks if a position is valid for player movement
// Returns false if out of bounds or colliding with a wall
bool	is_valid_position(float x, float y)
{
	int	map_x;
	int	map_y;

	if (!game()->map)
		return (false);
	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game()->map_width || map_y < 0
		|| map_y >= game()->map_height)
		return (false);
	return (game()->map[map_y][map_x] != '1');
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
		player->player_x += MOVE_SPEED * cos(player->player_dir - PI / 2);
		player->player_y += MOVE_SPEED * sin(player->player_dir - PI / 2);
	}
	if (player->key_right)
	{
		player->player_x += MOVE_SPEED * cos(player->player_dir + PI / 2);
		player->player_y += MOVE_SPEED * sin(player->player_dir + PI / 2);
	}
	if (player->key_rot_left)
		player->player_dir -= ROT_SPEED;
	if (player->key_rot_right)
		player->player_dir += ROT_SPEED;
} */
