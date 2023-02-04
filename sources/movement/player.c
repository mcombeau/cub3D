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
}

