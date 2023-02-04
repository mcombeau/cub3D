#include "cub3d.h"

void	init_player_direction(t_data *data)
{
	if (data->player.direction == 'N')
		data->player.view_angle = data->mapinfo.north;
	else if (data->player.direction == 'E')
		data->player.view_angle = data->mapinfo.east;
	else if (data->player.direction == 'S')
		data->player.view_angle = data->mapinfo.south;
	else if (data->player.direction == 'W')
		data->player.view_angle = data->mapinfo.west;
	data->player.pos_x = data->player.tile_x;
	data->player.pos_y = data->player.tile_y;
}
