#include "cub3d.h"

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	index;

	index = y * image->size_line + x * (image->pixel_bits / 8);
	image->addr[index] = color;
	image->addr[index + 1] = color >> 8;
	image->addr[index + 2] = color >> 16;
	image->addr[index + 3] = color >> 24;
}
