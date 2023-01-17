#include "cub3d.h"

int	key_event_handler(int keycode, t_cub3d *cub3d)
{
	if (keycode == KEY_ESC)
		quit_cub3d(cub3d);
	else
		return (1);
	return (0);
}
