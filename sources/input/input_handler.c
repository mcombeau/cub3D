#include "cub3d.h"

int	key_event_handler(int keycode, t_cub3d *cub3d)
{
	if (keycode == KEY_ESC)
		clean_exit(cub3d, 0);
	else
		return (1);
	return (0);
}
