#include "cub3d.h"

double	degrees_to_rad_converter(float degree)
{
	double radian;

	radian = degree *  PI / 180;
	return (radian);
}

double	calculate_distance(double deltaX, double deltaY)
{
	double	distance;

	distance = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	return (distance);
}

void	draw_line(void *mlx, void *window, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX;
	double deltaY = endY - beginY;

	int pixels = calculate_distance(deltaX, deltaY);

	deltaX /= pixels;
	deltaY /= pixels;

	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		mlx_pixel_put(mlx, window, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
}