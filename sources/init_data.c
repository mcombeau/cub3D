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

void	init_map(t_map *map)
{
	map->fd = 0;
	map->path = NULL;
	map->file = NULL;
	map->map = NULL;
}

void	init_data(t_data *data)
{
	ft_memset(&data->map, 0, sizeof(t_map));
	ft_memset(&data->img, 0, sizeof(t_img));
	init_textures(&data->textures);
	init_map(&data->map);
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
}
