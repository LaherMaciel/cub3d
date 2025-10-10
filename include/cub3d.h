/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 01:27:56 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/10/10 17:08:41 by lahermaciel      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

// MLX includes
# include "../libraries/minilibx-linux/mlx.h"

// Libft includes
# include "../libraries/libft/include/libft.h"

// Define window dimensions
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

// Define map constants
# define MAP_WIDTH 24
# define MAP_HEIGHT 24

// Define player constants
# define MOVE_SPEED 2.4
# define ROT_SPEED 0.1

// Define colors (RGB values)
# define COLOR_RED 0xFF0000
# define COLOR_GREEN 0x00FF00
# define COLOR_BLUE 0x0000FF
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLACK 0x000000
# define COLOR_YELLOW 0xFFFF00

typedef struct s_map
{
	char			*content;
	struct s_map	*next;
}				t_map;

typedef struct s_game
{
	void	*mlx;
	void	*window;
	void	*image;
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
	char	**map;
	double	player_x;
	double	player_y;
	double	player_dir; // Angle in radians
}				t_game;

typedef struct s_player
{
	float	player_x;
	float	player_y;
	float	player_dir; // Angle in radians
	bool	key_up;
	bool	key_down;
	bool	key_left;
	bool	key_right;
	bool	key_rot_left;
	bool	key_rot_right;
}				t_player;

//init structs
t_game		*game(void);
t_player	*player(void);

//close game
int			close_program(void);

//init functions
void		init_image(void);
void		init_game(void);
void		init_player(void);
void		init_map(char *filename);
void		convert_linked_list_to_array(t_map *head);

//linked list functions
int			ft_lstsize2(t_map *lst);
t_map		*ft_lstlast2(t_map *lst);
void		ft_lstdelone2(t_map *lst, void (*del)(void*));
void		ft_lstclear2(t_map **lst, void (*del)(void*));
void		ft_lstadd_back2(t_map **lst, t_map *new_node);
t_map		*ft_lstnew2(void *content);

//movement functions
int			key_press(int keycode, t_player *player);
int			key_release(int keycode, t_player *player);
void		move_player_2d(t_player *player);
void		move_player_3d(t_player *player);

//hooks
void		setup_hooks(void);

//drawing functions
int			draw_loop(void);
void		put_pixel(int x, int y, int color);
void		clear_screen(void);
void		draw_circle(int x, int y, int size);

#endif