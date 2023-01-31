#include "cub3d.h"

void	set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * image->size_line + x * (image->pixel_bits / 8);
	if (image->endian == 1)        // Most significant (Alpha) byte first
    {
        image->addr[pixel + 0] = (color >> 24);
        image->addr[pixel + 1] = (color >> 16) & 0xFF;
        image->addr[pixel + 2] = (color >> 8) & 0xFF;
        image->addr[pixel + 3] = (color) & 0xFF;
    }
    else if (image->endian == 0)   // Least significant (Blue) byte first
    {
        image->addr[pixel + 0] = (color) & 0xFF;
        image->addr[pixel + 1] = (color >> 8) & 0xFF;
        image->addr[pixel + 2] = (color >> 16) & 0xFF;
        image->addr[pixel + 3] = (color >> 24);
    }
	/* image->addr[index] = color; */
	/* image->addr[index + 1] = color >> 8; */
	/* image->addr[index + 2] = color >> 16; */
	/* image->addr[index + 3] = color >> 24; */
}
