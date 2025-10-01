/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:37:22 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/01 22:22:42 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	key_press(int keycode, t_player *player)
{
	ft_printf("key_press: %d\n", keycode);
	if (keycode == 65307)
		exit(EXIT_SUCCESS);
	else if (keycode == 119)
		player->key_up = true;
	else if (keycode == 115)
		player->key_down = true;
	else if (keycode == 97)
		player->key_left = true;
	else if (keycode == 100)
		player->key_right = true;
	else if (keycode == 65361)
		player->key_rot_left = true;
	else if (keycode == 65363)
		player->key_rot_right = true;
	else if (keycode == 65307)
		exit(EXIT_SUCCESS);
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	ft_printf("key_release: %d\n", keycode);
	if (keycode == 65307)
		exit(EXIT_SUCCESS);
	else if (keycode == 119)
		player->key_up = false;
	else if (keycode == 115)
		player->key_down = false;
	else if (keycode == 97)
		player->key_left = false;
	else if (keycode == 100)
		player->key_right = false;
	else if (keycode == 65361)
		player->key_rot_left = false;
	else if (keycode == 65363)
		player->key_rot_right = false;
	else if (keycode == 65307)
		exit(EXIT_SUCCESS);
	return (0);
}

void	move_player_2d(t_player *player)
{
	if (player->key_up && (player->player_y > 10))
		player->player_y -= MOVE_SPEED;
	if (player->key_down && (player->player_y < WINDOW_HEIGHT - 20))
		player->player_y += MOVE_SPEED;
	if (player->key_left && (player->player_x > 10))
		player->player_x -= MOVE_SPEED;
	if (player->key_right && (player->player_x < WINDOW_WIDTH - 20))
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
