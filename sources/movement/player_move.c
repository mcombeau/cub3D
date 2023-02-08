#include "cub3d.h"

static int	validate_move(t_data *data, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (data->map[(int)data->player.pos_y][(int)new_x] == '0')
	{
		data->player.pos_x = new_x;
		moved = 1;
	}
	if (data->map[(int)new_y][(int)data->player.pos_x] == '0')
	{
		data->player.pos_y = new_y;
		moved = 1;
	}
	return (moved);
}

int	move_player_forward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_x * MOVESPEED;
	new_y = data->player.pos_y + data->player.dir_y * MOVESPEED;
	return (validate_move(data, new_x, new_y));
}

int	move_player_backward(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_x * MOVESPEED;
	new_y = data->player.pos_y - data->player.dir_y * MOVESPEED;
	return (validate_move(data, new_x, new_y));
}

int	move_player_left(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x - data->player.dir_y * MOVESPEED;
	new_y = data->player.pos_y + data->player.dir_x * MOVESPEED;
	return (validate_move(data, new_x, new_y));
}

int	move_player_right(t_data *data)
{
	double	new_x;
	double	new_y;

	new_x = data->player.pos_x + data->player.dir_y * MOVESPEED;
	new_y = data->player.pos_y - data->player.dir_x * MOVESPEED;
	return (validate_move(data, new_x, new_y));
}
