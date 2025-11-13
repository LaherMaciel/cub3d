/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahermaciel <lahermaciel@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 01:27:56 by lahermaciel       #+#    #+#             */
/*   Updated: 2025/11/13 14:41:36 by lahermaciel      ###   ########.fr       */
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

# define PI 3.14159265359

// Define window dimensions
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

// Define map constants
# define MAP_WIDTH 24
# define MAP_HEIGHT 24
# define BLOCK 10
# define START_X 25
# define START_Y 25

// Define player constants
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05

/* ==== PRIMARY COLORS ==== */
# define COLOR_RED         0xFF0000
# define COLOR_RED_LIGHT   0xFF6666
# define COLOR_RED_DARK    0x800000

# define COLOR_GREEN       0x00FF00
# define COLOR_GREEN_LIGHT 0x66FF66
# define COLOR_GREEN_DARK  0x008000

# define COLOR_BLUE        0x0000FF
# define COLOR_BLUE_LIGHT  0x6666FF
# define COLOR_BLUE_DARK   0x000080

/* ==== NEUTRALS ==== */
# define COLOR_WHITE       0xFFFFFF
# define COLOR_WHITE_DARK  0xC0C0C0

# define COLOR_BLACK       0x000000
# define COLOR_BLACK_LIGHT 0x404040
# define COLOR_BLACK_DARK  0x000000

# define COLOR_GRAY        0x808080
# define COLOR_GRAY_LIGHT  0xA9A9A9
# define COLOR_GRAY_DARK   0x505050

/* ==== EXTRA COLORS ==== */
# define COLOR_YELLOW       0xFFFF00
# define COLOR_YELLOW_LIGHT 0xFFFF80
# define COLOR_YELLOW_DARK  0x808000

# define COLOR_CYAN         0x00FFFF
# define COLOR_CYAN_LIGHT   0x80FFFF
# define COLOR_CYAN_DARK    0x008080

# define COLOR_MAGENTA       0xFF00FF
# define COLOR_MAGENTA_LIGHT 0xFF80FF
# define COLOR_MAGENTA_DARK  0x800080

# define COLOR_ORANGE       0xFFA500
# define COLOR_ORANGE_LIGHT 0xFFBF66
# define COLOR_ORANGE_DARK  0x804000

# define COLOR_PURPLE       0x800080
# define COLOR_PURPLE_LIGHT 11691775
# define COLOR_PURPLE_DARK  0x400040

# define COLOR_PINK         0xFFC0CB
# define COLOR_PINK_LIGHT   0xFFD6DC
# define COLOR_PINK_DARK    0xFF8DA1

# define COLOR_BROWN        0x8B4513
# define COLOR_BROWN_LIGHT  0xCD853F
# define COLOR_BROWN_DARK   0x5C3317

// Define Keycodes
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_SHIFT 65505

typedef struct s_map
{
	char			*content;
	struct s_map	*next;
}				t_map;

typedef struct s_textures
{
	char	*no_path;	// North texture path
	char	*so_path;	// South texture path
	char	*we_path;	// West texture path
	char	*ea_path;	// East texture path
	char	*roof_path;	// Roof texture path (bonus)
	char	*floor_path;	// Floor texture path (bonus)
	void	*no_img;
	void	*so_img;
	void	*we_img;
	void	*ea_img;
	void	*roof_img;
	void	*floor_img;
	int		no_width;
	int		no_height;
	int		so_width;
	int		so_height;
	int		we_width;
	int		we_height;
	int		ea_width;
	int		ea_height;
	int		roof_width;
	int		roof_height;
	int		floor_width;
	int		floor_height;
}				t_textures;

typedef struct s_colors
{
	int	floor_rgb;		// Floor color as RGB integer
	int	ceiling_rgb;	// Ceiling color as RGB integer
}				t_colors;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	void		*image;
	char		*data_addr;
	int			bpp;
	int			size_line;
	int			endian;
	char		**map;
	int			map_width;
	int			map_height;
	double		player_x;
	double		player_y;
	double		player_dir; // Angle in radians
	char		player_orientation; // N, S, E, W
	int			window_width;
	int			window_height;
	bool		is_fullscreen;
	t_textures	textures;
	t_colors	colors;
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
	bool	key_shift;
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
void		init_config_parsing(void);

//parsing functions
int			parse_cub_file(char *filename);
int			parse_configuration(char **lines, int *line_index);
int			parse_map(char **lines, int line_index);
int			validate_map(void);
int			validate_map_closed(void);
int			validate_player_position(void);
int			convert_rgb_to_int(int r, int g, int b);
bool		is_map_line(char *line);
int			parse_texture_line(char *line, char **texture_path,
				char *texture_name);
int			parse_mandatory_textures(char *line, int *config_count);
int			parse_color_config(char *line, int *config_count);
int			parse_bonus_config(char *line);
void		set_player_direction(char orientation);
void		free_all(void);
void		error_exit(char *message, int code);

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
bool		is_valid_position(double x, double y);

//hooks
void		setup_hooks(void);

//drawing functions
int			draw_loop(void);
void		put_pixel(int x, int y, int color);
void		clear_screen(void);
void		draw_map_2d(void);
void		draw_map_grid(void);
void		draw_player_position(void);

//window functions
void		setup_window_hooks(void);
void		update_window_size(void);
int			handle_window_resize(int event, void *param);
void		toggle_fullscreen(void);

//raycasting
bool		is_wall(int x, int y);
void		fov(void);
void		draw_player_on_minimap(void);
void		draw_minimap_square(int start_x, int start_y, int size, int color);

//Utils functions
void		get_textures(void);

#endif