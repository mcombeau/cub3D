#ifndef CUB3D_H
# define CUB3D_H

# include "keys_linux.h"
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>

/* ---------------------------------------------------------------------------*
							MACROS
 --------------------------------------------------------------------------- */

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

/* MINIMAP MACROS */
# ifndef MMAP_PIXEL_SIZE
#  define MMAP_PIXEL_SIZE 128
# endif

# ifndef MMAP_VIEW_DIST
#  define MMAP_VIEW_DIST 4
# endif

# ifndef MMAP_TILE_SIZE
#  define MMAP_TILE_SIZE (MMAP_PIXEL_SIZE / (2 * MMAP_VIEW_DIST))
# endif

# ifndef MMAP_SIZE
#  define MMAP_SIZE (2 * MMAP_VIEW_DIST) + 1
# endif

# ifndef MMAP_COLOR_PLAYER
#  define MMAP_COLOR_PLAYER 0x00FF00
# endif

# ifndef MMAP_COLOR_WALL
#  define MMAP_COLOR_WALL 0xFFFFFF
# endif

# ifndef MMAP_COLOR_FLOOR
#  define MMAP_COLOR_FLOOR 0x000000
# endif

# ifndef MMAP_COLOR_SPACE
#  define MMAP_COLOR_SPACE 0xFF0000
# endif

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
} 						t_textures;

typedef struct s_mapinfo
{
	int			fd;
	int			line_count;
	char		*path;
	char		**file;
	int			height;
	int			width;
	int			index_end_of_map;
}				t_mapinfo;

typedef struct s_player
{
	char	direction;
	int		x;
	int		y;
}			t_player;

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
}				t_data;

/* ---------------------------------------------------------------------------*
							FUNCTIONS
 --------------------------------------------------------------------------- */

/* init.c */
void	init_mlx(t_data *data);
void	init_img(t_data *data, t_img *image, int width, int height);

/* exit.c */
void	clean_exit(t_data *data, int code);
int		msg(char *format, char *detail, int errno);
int		quit_cub3d(t_data *data);

/* input/input_handler.c */
int		key_event_handler(int keycode, t_data *data);

/* check_args.c */
int		check_args(char *arg);


void	parse_data(char *path, t_data *data);


int		get_file_data(t_data *data, char **map);


int		fill_color_textures(t_textures *textures, char *line, int j);


int		create_map(t_data *data, char **map, int i);


t_ulong	convert_rgb_to_hex(int *rgb_tab);
int		check_textures_validity(t_textures *textures);


int		check_map_validity(t_data *data, char **map_tab);


int		check_top_or_bottom(char **map_tab, int i, int j);
int		check_map_sides(t_mapinfo *map, char **map_tab);
int		check_left_side_is_closed(char **map_tab);
int		check_right_side_is_closed(char **map_tab);




void	free_tab(char **tab);
int		free_data(t_data *data);

void	init_data(t_data *data);

int		is_a_white_space(char c);
int		print_error(char *str);
size_t	find_biggest_len(t_mapinfo *map, int i);
int		skip_walls(char **map_tab);

/* render/render.c */
void	render(t_data *data);

/* render/image_utils.c */
void	set_image_pixel(t_img *image, int x, int y, int color);

/* render/minimap_render.c */
void	render_minimap(t_data *data);

/* render/minimap_image.c */
void	render_minimap_image(t_data *data, char **minimap);

/* debug/debug.c */
void	debug_display_data(t_data *data);
void	debug_print_char_tab(char **tab);
#endif

