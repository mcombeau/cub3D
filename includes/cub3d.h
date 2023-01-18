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

/* ---------------------------------------------------------------------------*
							MACROS
 --------------------------------------------------------------------------- */

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

# define SUCCESS 0
# define FAILURE -1


enum e_map_errors
{
	INCORRECT_MAP = 3,
	INFO_ALREADY_FILLED,
	WRONG_INPUT
};

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

typedef struct s_cub3d
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_cub3d;

typedef struct s_textures
{
	char	*dir_NO;
	char	*dir_SO;
	char	*dir_WE;
	char	*dir_EA;
	int		*floor;
	int		*ceiling;
}				t_textures;

typedef struct s_map
{
	int		fd;
	int		line_count;
	size_t	line_len;
	char	*path;
	char	**map_infos;
	int		nb_line;
	char	**map;
	int		index_end_of_map;
	char	player_dir;
	int		player_x;
	int		player_y;
}				t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_textures	textures;
	t_map		map;

}				t_data;

/* ---------------------------------------------------------------------------*
							FUNCTIONS
 --------------------------------------------------------------------------- */

/* init.c */
void	init_mlx(t_cub3d *cub3d);
void	init_img(t_cub3d *cub3d);

/* exit.c */
void	clean_exit(t_cub3d *cub3d, int code);
int		msg(char *format, char *detail, int errno);
int		quit_cub3d(t_cub3d *cub3d);

/* input/input_handler.c */
int		key_event_handler(int keycode, t_cub3d *cub3d);


int		check_input(char *arg);

void	free_double_tab(char **tab);

int		parse_data(t_data *data, t_textures *graphics, char **map);

void	create_map(char *path, t_data *data);

int		parse_map_description(t_data *data, char **file, int i);

int		check_info_retrieved(t_textures *texture);

int		check_map(t_map *map, char **map_tab);

int		check_top_or_bottom(char **map_tab, int i, int j);
int		check_map_sides(t_map *map, char **map_tab);
int		check_left_side_is_closed(char **map_tab);
int		check_right_side_is_closed(char **map_tab);

void	init_data(t_data *data);

int		print_error(char *str);
int		is_a_white_space(char c);

#endif

