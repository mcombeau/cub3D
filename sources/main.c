#include "cub3d.h"
#include "keys_linux.h"

int main(int ac, char **av)
{
	t_cub3d	cub3d;
	t_data data;

	if (ac != 2)
	{
		ft_putendl_fd("Bad arguments.", 2);
		return (1);
	}
	init_data(&data);
	if (check_input(av[1]) == FAILURE)
		return (print_error("Must be a .cub file"));
	create_map(av[1], &data);
	if (parse_data(&data, &data.textures, data.map.map_infos) == FAILURE)
		return (print_error("The infos on this map are invalid"));
	check_map(&data.map, data.map.map);
	init_mlx(&cub3d);
	mlx_hook(cub3d.win, EVENT_CLOSE_BTN, 0, quit_cub3d, &cub3d);
	mlx_key_hook(cub3d.win, key_event_handler, &cub3d);
	mlx_loop(cub3d.mlx);
	return (0);
}
