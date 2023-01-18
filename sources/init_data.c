#include "cub3d.h"

void	init_graphics(t_textures *texture)
{
	texture->dir_NO = NULL;
	texture->dir_SO = NULL;
	texture->dir_WE = NULL;
	texture->dir_EA = NULL;
	texture->floor = 0;
	texture->ceiling = 0;
}

void	init_data(t_data *data)
{
	init_graphics(&data->textures);
}