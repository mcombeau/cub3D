#include "cub3d.h"

void	clean_exit(t_cub3d *cub3d, int code)
{
	if (!cub3d)
		exit(code);
	if (cub3d->win && cub3d->mlx)
		mlx_destroy_window(cub3d->mlx, cub3d->win);
	if (cub3d->mlx)
	{
		mlx_loop_end(cub3d->mlx);
		mlx_destroy_display(cub3d->mlx);
		free(cub3d->mlx);
	}
	exit(code);
}

int	msg(char *format, char *detail, int errno)
{
	printf(format, detail);
	return (errno);
}

