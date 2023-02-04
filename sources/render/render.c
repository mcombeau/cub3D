#include "cub3d.h"

/* FIXME: This is a placeholder function for the raycasting image */
void	set_background_color(t_data *data)
{
	init_img(data, &data->img, WIN_WIDTH, WIN_HEIGHT);
	for (int y = 0; y < WIN_HEIGHT; y++)
		for (int x = 0; x < WIN_WIDTH; x++)
			set_image_pixel(&data->img, x, y, 0x00FF00);
}

void	render(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	set_background_color(data);
	render_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->minimap.img,
		MMAP_PIXEL_SIZE / (2 * MMAP_VIEW_DIST),
		WIN_HEIGHT - (MMAP_PIXEL_SIZE
			+ (MMAP_PIXEL_SIZE / (2 * MMAP_VIEW_DIST)) * 2));
}

