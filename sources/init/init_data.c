#include "cub3d.h"

void	init_img_clean(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
}

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
	mapinfo->line_count = 0;
	mapinfo->path = NULL;
	mapinfo->file = NULL;
	mapinfo->height = 0;
	mapinfo->width = 0;
	mapinfo->north = degrees_to_rad_converter(ANGLE_NORTH);
	mapinfo->east = degrees_to_rad_converter(ANGLE_EAST);
	mapinfo->south = degrees_to_rad_converter(ANGLE_SOUTH);
	mapinfo->west = degrees_to_rad_converter(ANGLE_WEST);
	mapinfo->index_end_of_map = 0;
}

void	init_player(t_player *player)
{
	player->direction = '\0';
	player->tile_x = 0;
	player->tile_y = 0;
	player->pos_x = 0.0;
	player->pos_y = 0.0;
	player->view_angle = 0.0;
	player->dir_x = 0.0;
	player->dir_y = 0.0;
	player->plane_x = 0.0;
	player->plane_y = 0.0;
	player->has_moved = true;
}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->win_height = WIN_HEIGHT;
	data->win_width = WIN_WIDTH;
	init_player(&data->player);
	init_textures(&data->textures);
	data->map = NULL;
	init_mapinfo(&data->mapinfo);
	init_img_clean(&data->img);
	init_img_clean(&data->minimap);
}
