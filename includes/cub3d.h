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
#  define DEBUG_MSG 1
# endif

# define PI 3.1415926535 

# define ANGLE_EAST 0
# define ANGLE_SOUTH 90
# define ANGLE_WEST 180
# define ANGLE_NORTH 270

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

/* MINIMAP MACROS */
# define MMAP_PIXEL_SIZE 128
# define MMAP_VIEW_DIST 4
# define MMAP_COLOR_PLAYER 0x00FF00
# define MMAP_COLOR_WALL 0xFFFFFF
# define MMAP_COLOR_FLOOR 0x000000
# define MMAP_COLOR_SPACE 0xFF0000

// ERROR MESSAGES
# define ERR_WRONG_FILE "Is not an existing .cub file\n"
# define ERR_MISSING_INFO "The .cub file is missing some info.\n"
# define ERR_INVALID_INFO "The infos of this map are invalid.\n"
# define ERR_WRONG_NB_ARG "Correct usage is ./cub3d <map.cub>\n"
# define ERR_DIRECTION "At least one direction is missing or the input is wrong"
# define ERR_FLOOR_CEILING "The floor or ceiling info is wrong or missing."
# define ERR_INVALID_MAP "Map description is either wrong or incomplete."

enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE = 4
};

typedef unsigned long	t_ulong;

/* ---------------------------------------------------------------------------*
							STRUCTURES
 --------------------------------------------------------------------------- */

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
}	t_img;

typedef struct s_textures
{
	char				*north;
	char				*south;
	char				*west;
	char				*east;
	int					*floor;
	int					*ceiling;
	unsigned long		hex_floor;
	unsigned long		hex_ceiling;
}	t_textures;

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
	double		north;
	double		east;
	double		south;
	double		west;
	int			index_end_of_map;
}				t_mapinfo;

typedef struct s_player
{
	char	direction;
	int		tile_x;
	int		tile_y;
	double	pos_x;
	double	pos_y;
	double	view_angle;
	double	dir_x;
	double	dir_y;
	bool	has_moved;
}	t_player;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_player	player;
	t_textures	textures;
	char		**map;
	t_mapinfo	mapinfo;
	t_img		img;
	t_img		minimap;
	int			pixel;
}	t_data;

/* ---------------------------------------------------------------------------*
							FUNCTIONS
 --------------------------------------------------------------------------- */

/* init/init_data.c */
void	init_data(t_data *data);

/* init/init_mlx.c */
void	init_mlx(t_data *data);
void	init_img(t_data *data, t_img *image, int width, int height);

/* exit.c */
void	clean_exit(t_data *data, int code);
int		msg(char *format, char *detail, int errno);
int		quit_cub3d(t_data *data);

/* input/input_handler.c */
int		key_press_handler(int key, t_data *data);
int		key_release_handler(int key, t_data *data);

/* parsing/check_args.c */
int		check_args(char *arg);

/* parsing/parse_data.c */
void	parse_data(char *path, t_data *data);

/* parsing/get_file_data.c */
int		get_file_data(t_data *data, char **map);
int		fill_color_textures(t_textures *textures, char *line, int j);

/* parsing/create_game_map.c */
int		create_map(t_data *data, char **map, int i);

/* parsing/check_textures.c */
t_ulong	convert_rgb_to_hex(int *rgb_tab);
int		check_textures_validity(t_textures *textures);

/* parsing/check_gap.c */
int		check_map_validity(t_data *data, char **map_tab);

/* parsing/check_map_borders.c */
int		check_top_or_bottom(char **map_tab, int i, int j);
int		check_map_sides(t_mapinfo *map, char **map_tab);
int		check_left_side_is_closed(char **map_tab);
int		check_right_side_is_closed(char **map_tab);

/* parsing/parsing_utils.c */
int		is_a_white_space(char c);
int		print_error(char *str);
size_t	find_biggest_len(t_mapinfo *map, int i);
int		skip_walls(char **map_tab);

/* render/render.c */
int		render(t_data *data);

/* render/image_utils.c */
void	set_image_pixel(t_img *image, int x, int y, int color);

/* render/minimap_render.c */
void	render_minimap(t_data *data);

/* render/minimap_image.c */
void	render_minimap_image(t_data *data, t_minimap *minimap);

/*  raycasting_utils.c  */
double	degrees_to_rad_converter(float degree);
double	calculate_distance(double deltaX, double deltaY);
void	draw_line(void *mlx, void *window, int beginX, int beginY, int endX, int endY, int color);

/* input/input_handler.c */
int		key_event_handler(int keycode, t_data *data);

/* movement/player.c */
void	init_player_direction(t_data *data);

/* exit/exit.c */
void	clean_exit(t_data *data, int code);
int		msg(char *format, char *detail, int errno);
int		quit_cub3d(t_data *data);

/* exit/free_data.c */
void	free_tab(char **tab);
int		free_data(t_data *data);

/* debug.c */
void	debug_display_data(t_data *data);
void	debug_display_minimap(t_minimap *minimap);
void	debug_print_char_tab(char **tab);

#endif

