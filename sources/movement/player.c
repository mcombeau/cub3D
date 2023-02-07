#include "cub3d.h"

void	update_player_dir(t_player *player, double angle,
					double dir_x, double dir_y, double plane_x, double plane_y)
{
	player->view_angle = angle;
	player->dir_x = dir_x;
	player->dir_y = dir_y;
	player->plane_x = plane_x;
	player->plane_y = plane_y;
}

void	init_player_direction(t_data *data)
{
	if (data->player.direction == 'N')
		update_player_dir(&data->player, data->mapinfo.north, 0, -1, 0, 0.66);
	else if (data->player.direction == 'E')
		update_player_dir(&data->player, data->mapinfo.east, 1, 0, 0.66, 0);
	else if (data->player.direction == 'S')
		update_player_dir(&data->player, data->mapinfo.south, 0, 1, 0, -0.66);
	else if (data->player.direction == 'W')
		update_player_dir(&data->player, data->mapinfo.west, -1, 0, -0.66, 0);
	data->player.pos_x = data->player.tile_x;
	data->player.pos_y = data->player.tile_y;
}

void	update_player_tile(t_player *player)
{
	player->tile_x = (int)player->pos_x;
	player->tile_y = (int)player->pos_y;
}
