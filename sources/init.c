#include "cub3d.h"

void	init_img(t_cub3d *cub3d)
{
	cub3d->img.img = mlx_new_image(cub3d->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub3d->img.img)
		clean_exit(cub3d, msg("cub3d: %s\n", "image creation error.", 1));
	cub3d->img.addr = mlx_get_data_addr(cub3d->img.img, &cub3d->img.size_line,
			&cub3d->img.size_line, &cub3d->img.endian);
	return ;
}

void	init_mlx(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		clean_exit(cub3d, msg("cub3D: %s\n", "mlx: error starting mlx.", 1));
	cub3d->win = mlx_new_window(cub3d->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!cub3d->win)
		clean_exit(cub3d, msg("cub3D: %s\n", "mlx: error creating window.", 1));
	return ;
}
