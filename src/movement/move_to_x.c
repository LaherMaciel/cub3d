/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_to_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 22:02:31 by lahermaciel       #+#    #+#             */
/*   Updated: 2026/01/09 22:46:16 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

float	confirm_y(float try_x, float new_y, float r)
{
	float	try_y;
	float	x;

	try_y = new_y;
	x = try_x;
	if (new_y > game()->player_y)
	{
		if (!is_valid_position(x, try_y + r))
			try_y = (int)(try_y + r) - r;
	}
	else if (new_y < game()->player_y)
	{
		if (!is_valid_position(x, try_y - r))
			try_y = (int)(try_y - r) + 1 + r;
	}
	return (try_y);
}

void	move_to_new_x(float new_x, float new_y)
{
	float	try_x;
	float	try_y;
	float	r;

	try_x = new_x;
	try_y = game()->player_y;
	r = 0.2;
	if (new_x > game()->player_x)
	{
		if (!is_valid_position(try_x + r, game()->player_y))
			try_x = (int)(try_x + r) - r;
	}
	else if (new_x < game()->player_x)
	{
		if (!is_valid_position(try_x - r, game()->player_y))
			try_x = (int)(try_x - r) + 1 + r;
	}
	try_y = confirm_y(try_x, new_y, r);
	game()->player_x = try_x;
	game()->player_y = try_y;
}
