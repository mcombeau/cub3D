#include "cub3d.h"

int	rotate_left_right(t_data *data)
{
	t_player	*p;
	double		tmp_x;
	double		rotspeed;

	p = &data->player;
	rotspeed = ROTSPEED * p->rotate;
	tmp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rotspeed) - p->dir_y * sin(rotspeed);
	p->dir_y = tmp_x * sin(rotspeed) + p->dir_y * cos(rotspeed);
	tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rotspeed) - p->plane_y * sin(rotspeed);
	p->plane_y = tmp_x * sin(rotspeed) + p->plane_y * cos(rotspeed);
	data->player.has_moved = true;
	return (1);
}
