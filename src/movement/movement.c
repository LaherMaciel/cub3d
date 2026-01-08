/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karocha- <karocha-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:37:22 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/04 10:21:02 by karocha-         ###   ########.fr       */
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
	printf("\n\nmap_x: %d, map_y: %d\n", map_x, map_y);
	printf("Position (%.2f, %.2f)	", x, y);
	if (map_x < 0 || map_x >= game()->map_width || map_y < 0
		|| map_y >= game()->map_height)
	{
		printf("1Position is out of bounds\n");
		printf("False\n\n");
		return (false);
	}
	if (game()->map[map_y][map_x] == '1')
	{
		if (x < game()->player_x && x >= map_x + 0.8)
		{
			if (game()->map[map_y][(int)game()->player_x] != '1')
				game()->player_y = y;
			printf("1 X Colliding with wall moving only Y\n");
			printf("False\n\n");
			return (false);
		}
		if (x < game()->player_x && x <= map_x + 0.2)
		{
			if (game()->map[map_y][(int)game()->player_x] != '1')
				game()->player_y = y;
			printf("2 X Colliding with wall moving only Y\n");
			printf("False\n\n");
			return (false);
		}
		if (y < game()->player_y && y >= map_y + 0.8)
		{
			if (game()->map[(int)game()->player_y][map_x] != '1')
				game()->player_x = x;
			printf("1 Y Colliding with wall moving only X\n");
			printf("False\n\n");
			return (false);
		}
		if (y < game()->player_y && y <= map_y + 0.2)
		{
			if (game()->map[(int)game()->player_y][map_x] != '1')
				game()->player_x = x;
			printf("2 Y Colliding with wall moving only X\n");
			printf("False\n\n");
			return (false);
		}
		printf("x(%) < game()->player_x && x >= map_x + 0.8\n", x, game()->player_x,
			map_x + 0.8);
		printf("2 Position is out of bounds\n");
		printf("False\n\n");
		return (false);
	}
	printf("\nTrue\n\n");
	return (true);
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
