#include "cub3d.h"

static void	move_player(t_data *data, int key)
{
	if (key == XK_w)
	{
		printf("Move player forward\n");
		data->player.pos_x += data->player.dir_x * MOVESPEED;
		data->player.pos_y += data->player.dir_y * MOVESPEED;
	}
	else if (key == XK_s)
	{
		printf("Move player backward\n");
		data->player.pos_x -= data->player.dir_x * MOVESPEED;
		data->player.pos_y -= data->player.dir_y * MOVESPEED;
	}
	else if (key == XK_a)
	{
		printf("Move player left\n");
		data->player.pos_x -= data->player.dir_y * MOVESPEED;
		data->player.pos_y += data->player.dir_x * MOVESPEED;
	}
	else if (key == XK_d)
	{
		printf("Move player right\n");
		data->player.pos_x += data->player.dir_y * MOVESPEED;
		data->player.pos_y -= data->player.dir_x * MOVESPEED;
	}
}

static bool	is_valid_move(t_data *data)
{
	if ((int)data->player.pos_x > data->mapinfo.width)
		return (false);
	if ((int)data->player.pos_y > data->mapinfo.height)
		return (false);
	if (data->map[(int)data->player.pos_y][(int)data->player.pos_x] != '0')
		return (false);
	return (true);
}

void	handle_player_move(t_data *data, int key)
{
	double	tmp_x;
	double	tmp_y;

	tmp_x = data->player.pos_x;
	tmp_y = data->player.pos_y;
	move_player(data, key);
	if (is_valid_move(data) == false)
	{
		data->player.pos_x = tmp_x;
		data->player.pos_y = tmp_y;
		return ;
	}
	update_player_tile(&data->player);
	data->player.has_moved = true;
}

void	handle_player_rotate(t_data *data, int key)
{
	t_player	*p;
	double		tmp_x;
	double		rotspeed;

	p = &data->player;
	rotspeed = ROTSPEED;
	if (key == XK_Right)
	{
		printf("Rotate player right\n");
		rotspeed *= -1;
	}
	else
		printf("Rotate player left\n");
	tmp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rotspeed) - p->dir_y * sin(rotspeed);
	p->dir_y = tmp_x * sin(rotspeed) + p->dir_y * cos(rotspeed);
	tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rotspeed) - p->plane_y * sin(rotspeed);
	p->plane_y = tmp_x * sin(rotspeed) + p->plane_y * cos(rotspeed);
}
