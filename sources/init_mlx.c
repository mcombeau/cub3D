#include "cub3d.h"

void	init_img(t_data *data)
{
	data->img.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img.img)
		clean_exit(data, msg("cub3d: %s\n", "image creation error.", 1));
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.size_line,
			&data->img.size_line, &data->img.endian);
	return ;
}

void	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		clean_exit(data, msg("cub3D: %s\n", "mlx: error starting mlx.", 1));
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!data->win)
		clean_exit(data, msg("cub3D: %s\n", "mlx: error creating window.", 1));
	return ;
}
