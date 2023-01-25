#include "cub3d.h"
#include "keys_linux.h"

int main(int ac, char **av)
{
	t_cub3d	cub3d;
	t_data data;

	if (ac != 2)
	{
		ft_putendl_fd(ERR_WRONG_NB_ARG, 2);
		return (1);
	}
	init_data(&data);
	if (check_args(av[1]) == FAILURE)
		return (print_error(ERR_WRONG_FILE));
	parse_data(av[1], &data);
	if (get_file_data(&data, data.map.file) == FAILURE)
		return (free_data(&data));
	if (check_textures_validity(&data.textures) == FAILURE)
		return (print_error(ERR_INVALID_INFO) && free_data(&data));
	if (check_map_validity(&data.map, data.map.map) == FAILURE)
		return (print_error(ERR_INVALID_INFO) && free_data(&data));
	init_mlx(&cub3d);
	mlx_hook(cub3d.win, EVENT_CLOSE_BTN, 0, quit_cub3d, &cub3d);
	mlx_key_hook(cub3d.win, key_event_handler, &cub3d);
	mlx_loop(cub3d.mlx);
	return (0);
}
