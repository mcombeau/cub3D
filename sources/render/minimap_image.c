#include "cub3d.h"

static void	set_minimap_pixel(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MMAP_TILE_SIZE)
	{
		j = 0;
		while (j < MMAP_TILE_SIZE)
		{
			set_image_pixel(&data->minimap, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void	set_minimap_image_pixels(t_data *data, char **minimap)
{
	int	x;
	int	y;

	y = 0;
	while (y < MMAP_SIZE)
	{
		x = 0;
		while (x < MMAP_SIZE)
		{
			if (minimap[y][x] == '\0')
				break ;
			if (minimap[y][x] == 'P')
				set_minimap_pixel(data, x * MMAP_TILE_SIZE, y * MMAP_TILE_SIZE,
					MMAP_COLOR_PLAYER);
			else if (minimap[y][x] == '1')
				set_minimap_pixel(data, x * MMAP_TILE_SIZE, y * MMAP_TILE_SIZE,
					MMAP_COLOR_WALL);
			else if (minimap[y][x] == '0')
				set_minimap_pixel(data, x * MMAP_TILE_SIZE, y * MMAP_TILE_SIZE,
					MMAP_COLOR_FLOOR);
			else if (minimap[y][x] == ' ')
				set_minimap_pixel(data, x * MMAP_TILE_SIZE, y * MMAP_TILE_SIZE,
					MMAP_COLOR_SPACE);
			x++;
		}
		y++;
	}
}

static void	set_minimap_border_image_pixels(t_data *data, int color)
{
	int	size;
	int	x;
	int	y;

	size = MMAP_PIXEL_SIZE + MMAP_TILE_SIZE;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x <= size)
		{
			if (x < 5 || x > size - 5 || y < 5 || y > size - 5)
				set_image_pixel(&data->minimap, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_minimap_image(t_data *data, char **minimap)
{
	int	img_size;

	img_size = MMAP_PIXEL_SIZE + MMAP_TILE_SIZE;
	init_img(data, &data->minimap, img_size, img_size);
	set_minimap_image_pixels(data, minimap);
	set_minimap_border_image_pixels(data, MMAP_COLOR_SPACE);
}
