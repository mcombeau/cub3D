#include "cub3d.h"

void	init_frame_pixels(t_data *data)
{
	int	i;

	if (data->pixels)
		free_tab((void **)data->pixels);
	data->pixels = ft_calloc(data->win_height + 1,
			sizeof * data->pixels);
	if (!data->pixels)
		clean_exit(data, msg("cub3d: %s\n", "malloc error.", 1));
	i = 0;
	while (i < data->win_width)
	{
		data->pixels[i] = ft_calloc(data->win_width + 1,
				sizeof * data->pixels);
		if (!data->pixels[i])
			clean_exit(data, msg("cub3d: %s\n", "malloc error.", 1));
		i++;
	}
}

void	render_frame(t_data *data)
{
	t_img	image;
	int		x;
	int		y;

	init_img(data, &image, data->win_width, data->win_height);
	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			if (data->pixels[y][x] > 0)
				set_image_pixel(&image, x, y, data->pixels[y][x]);
			else if (y < data->win_height / 2)
				set_image_pixel(&image, x, y, data->texinfo.hex_ceiling);
			else
				set_image_pixel(&image, x, y, data->texinfo.hex_floor);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, image.img, 0, 0);
	mlx_destroy_image(data->mlx, image.img);
}

/* FIXME: This is a placeholder function for the raycasting image */
void	set_background_color(t_data *data)
{
	t_img	image;

	init_img(data, &image, WIN_WIDTH, WIN_HEIGHT);
	for (int y = 0; y < WIN_HEIGHT; y++)
		for (int x = 0; x < WIN_WIDTH; x++)
			set_image_pixel(&image, x, y, 0x00FF00);
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

int	render(t_data *data)
{
	bool	moved;

	moved = false;
	moved = has_player_moved(data);
	if (!moved)
		return (0);
	mlx_clear_window(data->mlx, data->win);
	set_background_color(data);
	render_minimap(data);
	/* mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0); */
	/* mlx_put_image_to_window(data->mlx, data->win, data->minimap.img, */
	/* 	MMAP_PIXEL_SIZE / (2 * MMAP_VIEW_DIST), */
	/* 	WIN_HEIGHT - (MMAP_PIXEL_SIZE */
	/* 		+ (MMAP_PIXEL_SIZE / (2 * MMAP_VIEW_DIST)) * 2)); */
	return (0);
}
