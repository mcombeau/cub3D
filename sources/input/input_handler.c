#include "cub3d.h"

int	key_press_handler(int key, t_data *data)
{
	/* printf("Key was pressed.\n"); */
	if (key == XK_Escape)
		quit_cub3d(data);
	if (key == XK_Left || key == XK_Right)
		handle_player_rotate(data, key);
	if (key == XK_w || key == XK_a || key == XK_s || key == XK_d)
		handle_player_move(data, key);
	else
		return (1);
	return (0);
}

int	key_release_handler(int key, t_data *data)
{
	/* printf("Key was released.\n"); */
	(void)data;
	(void)key;
	return (0);
}
