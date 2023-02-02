#include "cub3d.h"

void	init_textures(t_textures *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->floor = 0;
	textures->ceiling = 0;
}

void	init_mapinfo(t_mapinfo *mapinfo)
{
	mapinfo->fd = 0;
	mapinfo->path = NULL;
	mapinfo->file = NULL;
}

void	init_data(t_data *data)
{
	ft_memset(&data->mapinfo, 0, sizeof(t_mapinfo));
	ft_memset(&data->img, 0, sizeof(t_img));
	init_textures(&data->textures);
	data->map = NULL;
	init_mapinfo(&data->mapinfo);
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
}
