#include "cub3d.h"

static void	set_minimap_pixel(t_minimap *minimap, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < minimap->tile_size)
	{
		j = 0;
		while (j < minimap->tile_size)
		{
			set_image_pixel(minimap->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void	set_minimap_image_pixels(t_minimap *minimap)
{
	int	x;
	int	y;

	y = 0;
	while (y < minimap->size)
	{
		x = 0;
		while (x < minimap->size)
		{
			if (minimap->map[y][x] == '\0')
				break ;
			if (minimap->map[y][x] == 'P')
				set_minimap_pixel(minimap, x * minimap->tile_size,
					y * minimap->tile_size, MMAP_COLOR_PLAYER);
			else if (minimap->map[y][x] == '1')
				set_minimap_pixel(minimap, x * minimap->tile_size,
					y * minimap->tile_size, MMAP_COLOR_WALL);
			else if (minimap->map[y][x] == '0')
				set_minimap_pixel(minimap, x * minimap->tile_size,
					y * minimap->tile_size, MMAP_COLOR_FLOOR);
			else if (minimap->map[y][x] == ' ')
				set_minimap_pixel(minimap, x * minimap->tile_size,
					y * minimap->tile_size, MMAP_COLOR_SPACE);
			x++;
		}
		y++;
	}
}

static void	set_minimap_border_image_pixels(t_minimap *minimap, int color)
{
	int	size;
	int	x;
	int	y;

	size = MMAP_PIXEL_SIZE + minimap->tile_size;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x <= size)
		{
			if (x < 5 || x > size - 5 || y < 5 || y > size - 5)
				set_image_pixel(minimap->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	render_minimap_image(t_data *data, t_minimap *minimap)
{
	int	img_size;

	img_size = MMAP_PIXEL_SIZE + minimap->tile_size;
	init_img(data, &data->minimap, img_size, img_size);
	set_minimap_image_pixels(minimap);
	set_minimap_border_image_pixels(minimap, MMAP_COLOR_SPACE);
}
