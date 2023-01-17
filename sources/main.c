#include "cub3d.h"
#include "keys_linux.h"

int main(int ac, char **av)
{
	t_cub3d	cub3d;

	if (ac != 2)
	{
		ft_putendl_fd("Bad arguments.", 2);
		return (1);
	}
	(void)av;
	init_mlx(&cub3d);
	mlx_hook(cub3d.win, EVENT_CLOSE_BTN, 0, quit_cub3d, &cub3d);
	mlx_key_hook(cub3d.win, key_event_handler, &cub3d);
	mlx_loop(cub3d.mlx);
	return (0);
}
