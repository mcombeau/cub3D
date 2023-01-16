#ifndef CUB3D_H
# define CUB3D_H

# include "keys_linux.h"
# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>

/* ---------------------------------------------------------------------------*
							MACROS
 --------------------------------------------------------------------------- */

# define WIN_WIDTH 640
# define WIN_HEIGHT 480

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

/* ---------------------------------------------------------------------------*
							FUNCTIONS
 --------------------------------------------------------------------------- */

/* init.c */
void	init_mlx(t_cub3d *cub3d);
void	init_img(t_cub3d *cub3d);

/* exit.c */
void	clean_exit(t_cub3d *cub3d, int code);
int		msg(char *format, char *detail, int errno);

/* input/input_handler.c */
int		key_event_handler(int keycode, t_cub3d *cub3d);

#endif

