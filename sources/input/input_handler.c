#include "cub3d.h"

int	key_press_handler(int key, t_data *data)
{
	printf("Key was pressed.\n");
	if (key == XK_Escape)
		quit_cub3d(data);
	else
		return (1);
	return (0);
}

int	key_release_handler(int key, t_data *data)
{
	printf("Key was released.\n");
	(void)data;
	(void)key;
	return (0);
}
