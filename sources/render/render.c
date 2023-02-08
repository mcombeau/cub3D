#include "cub3d.h"

#define DEBUG_COLOR_WALL	0xFF0000
#define DEBUG_COLOR_CEILING 0xAAAAAA
#define DEBUG_COLOR_FLOOR	0x666666

void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	if (data->texture_pixels[y][x] > 0)
		image->addr[y * data->win_width + x] = data->texture_pixels[y][x];
	else if (y < data->win_height / 2)
		image->addr[y * data->win_width + x] = data->texinfo.hex_ceiling;
	else if (y < data->win_height -1)
		image->addr[y * data->win_width + x] = data->texinfo.hex_floor;
}

void	render_frame(t_data *data)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	init_img(data, &image, data->win_width, data->win_height);
	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			set_frame_image_pixel(data, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, image.img, 0, 0);
	mlx_destroy_image(data->mlx, image.img);
}

static bool	has_player_moved(t_data *data)
{
	if (data->player.has_moved == true)
	{
		data->player.has_moved = false;
		return (true);
	}
	return (false);
}

void	render_raycast(t_data *data)
{
	init_texture_pixels(data);
	init_ray(&data->ray);
	raycasting(&data->player, data);
	render_frame(data);
}

int	render(t_data *data)
{
	bool	moved;

	moved = false;
	moved = has_player_moved(data);
	if (!moved)
		return (0);
	mlx_clear_window(data->mlx, data->win);
	render_raycast(data);
	/* render_minimap(data); */
	return (0);
}
