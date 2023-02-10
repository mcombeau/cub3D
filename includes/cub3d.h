/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexa <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:47:42 by alexa             #+#    #+#             */
/*   Updated: 2023/02/10 14:26:30 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "colors.h"
# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>

/* ---------------------------------------------------------------------------*
							MACROS
 --------------------------------------------------------------------------- */

# ifndef DEBUG_MSG
#  define DEBUG_MSG 0
# endif

# ifndef MMAP_DEBUG_MSG
#  define MMAP_DEBUG_MSG 0
# endif

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

# define TEX_SIZE 64

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# define MOVESPEED 0.025
# define ROTSPEED 0.03

# define DIST_EDGE_MOUSE_WRAP 20

/* MINIMAP MACROS */
# define MMAP_PIXEL_SIZE 128
# define MMAP_VIEW_DIST 4
# define MMAP_COLOR_PLAYER 0x00FF00
# define MMAP_COLOR_WALL 0x808080
# define MMAP_COLOR_FLOOR 0xE6E6E6
# define MMAP_COLOR_SPACE 0x404040

// ERROR MESSAGES
# define ERR_WRONG_FILE "Is not an existing .cub file\n"
# define ERR_MISSING_INFO "The .cub file is missing some info.\n"
# define ERR_INVALID_INFO "The infos of this map are invalid.\n"
# define ERR_WRONG_NB_ARG "Correct usage is ./cub3d <map.cub>\n"
# define ERR_DIRECTION "At least one direction is missing or the input is wrong"
# define ERR_FLOOR_CEILING "The floor or ceiling info is wrong or missing."
# define ERR_INVALID_MAP "Map description is either wrong or incomplete."
# define ERR_INV_LETTER "There is an invalid letter in the map."
# define ERR_NUM_PLAYER "There is more than one player in the map"

enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE = 4
};

enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3
};

typedef unsigned long	t_ulong;

/* ---------------------------------------------------------------------------*
							STRUCTURES
 --------------------------------------------------------------------------- */

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_texinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	unsigned long	hex_floor;
	unsigned long	hex_ceiling;
	int				size;
	int				index;
	double			step;
	double			pos;
	int				x;
	int				y;
}	t_texinfo;

typedef struct s_minimap
{
	char	**map;
	t_img	*img;
	int		size;
	int		offset_x;
	int		offset_y;
	int		view_dist;
	int		tile_size;
}	t_minimap;

typedef struct s_mapinfo
{
	int			fd;
	int			line_count;
	char		*path;
	char		**file;
	int			height;
	int			width;
	int			index_end_of_map;
}	t_mapinfo;

typedef struct s_ray
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	wall_dist;
	double	wall_x;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		has_moved;
	int		move_x;
	int		move_y;
	int		rotate;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_mapinfo	mapinfo;
	char		**map;
	t_player	player;
	t_ray		ray;
	int			**texture_pixels;
	int			**textures;
	t_texinfo	texinfo;
	t_img		minimap;
}	t_data;

/* ---------------------------------------------------------------------------*
							FUNCTIONS
 --------------------------------------------------------------------------- */

/* init/init_data.c */
void	init_data(t_data *data);
void	init_img_clean(t_img *img);
void	init_ray(t_ray *ray);

/* init/init_mlx.c */
void	init_mlx(t_data *data);
void	init_img(t_data *data, t_img *image, int width, int height);
void	init_texture_img(t_data *data, t_img *image, char *path);

/* init/init_textures.c */
void	init_textures(t_data *data);
void	init_texinfo(t_texinfo *textures);

/* parsing/check_args.c */
int		check_args(char *arg);

/* parsing/parse_data.c */
void	parse_data(char *path, t_data *data);

/* parsing/get_file_data.c */
int		get_file_data(t_data *data, char **map);

/* parsing/fill_color_textures.c */
int		fill_color_textures(t_texinfo *textures, char *line, int j);

/* parsing/create_game_map.c */
int		create_map(t_data *data, char **map, int i);

/* parsing/check_textures.c */
int		check_textures_validity(t_texinfo *textures);

/* parsing/check_map.c */
int		check_map_validity(t_data *data, char **map_tab);

/* parsing/check_map_borders.c */
int		check_map_sides(t_mapinfo *map, char **map_tab);

/* parsing/parsing_utils.c */
int		is_a_white_space(char c);
int		print_error(char *str);
size_t	find_biggest_len(t_mapinfo *map, int i);

/* render/render.c */
int		render(t_data *data);
void	render_images(t_data *data);

/* render/raycasting.c */
int		raycasting(t_player *player, t_data *data);

/* render/texture.c */
void	init_texture_pixels(t_data *data);
void	update_texture_pixels(t_data *data, t_texinfo *tex, t_ray *ray, int x);

/* render/image_utils.c */
void	set_image_pixel(t_img *image, int x, int y, int color);

/* render/minimap_render.c */
void	render_minimap(t_data *data);

/* render/minimap_image.c */
void	render_minimap_image(t_data *data, t_minimap *minimap);

/* movement/input_handler.c */
int		key_press_handler(int key, t_data *data);
int		key_release_handler(int key, t_data *data);
int		mouse_motion_handler(int x, int y, t_data *data);

/* movement/player_dir.c */
void	init_player_direction(t_data *data);

/* movement/player_pos.c */
int		validate_move(t_data *data, double new_x, double new_y);

/* movement/player_move.c */
int		move_player(t_data *data);

/* movement/player_rotate.c */
int		rotate_player(t_data *data, double rotdir);

/* exit/exit.c */
void	clean_exit(t_data *data, int code);
int		msg(char *format, char *detail, int errno);
int		quit_cub3d(t_data *data);

/* exit/exit.c */
void	clean_exit(t_data *data, int code);
int		msg(char *format, char *detail, int errno);
int		quit_cub3d(t_data *data);

/* exit/free_data.c */
void	free_tab(void **tab);
int		free_data(t_data *data);

/* debug/debug.c */
void	debug_display_data(t_data *data);
void	debug_display_minimap(t_minimap *minimap);
void	debug_display_player(t_data *data);
void	debug_print_char_tab(char **tab);

#endif
