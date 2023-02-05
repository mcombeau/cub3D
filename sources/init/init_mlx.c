#include "cub3d.h"

void	init_img(t_data *data, t_img *image, int width, int height)
{
	if (DEBUG_MSG)
		printf(GREEN "Creating new image: WIDTH = %d, HEIGHT = %d\n" RESET,
			width, height);
	if (image->img != NULL)
		mlx_destroy_image(data->mlx, image->img);
	image->img = mlx_new_image(data->mlx, width, height);
	if (image->img == NULL)
		clean_exit(data, msg("cub3d: %s\n", "image creation error.", 1));
	image->addr = mlx_get_data_addr(image->img, &image->pixel_bits,
			&image->size_line, &image->endian);
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