#include "cub3d.h"

int	key_event_handler(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		quit_cub3d(data);
	else
		return (1);
	return (0);
}
