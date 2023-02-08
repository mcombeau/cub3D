#include "cub3d.h"

void	init_player_north_south(t_player *player)
{
	if (player->direction == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (player->direction == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else
		return ;
}

void	init_player_east_west(t_player *player)
{
	if (player->direction == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (player->direction == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	else
		return ;
}

void	init_player_direction(t_data *data)
{
	init_player_north_south(&data->player);
	init_player_east_west(&data->player);
	data->player.pos_x = data->player.tile_x;
	data->player.pos_y = data->player.tile_y;
}

void	update_player_tile(t_player *player)
{
	player->tile_x = (int)player->pos_x;
	player->tile_y = (int)player->pos_y;
}
