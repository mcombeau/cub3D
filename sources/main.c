#include "cub3d.h"
#include "keys_linux.h"

int	parse_args(t_data *data, char **av)
{
	if (check_args(av[1]) == FAILURE)
		return (print_error(ERR_WRONG_FILE));
	parse_data(av[1], data);
	if (get_file_data(data, data->mapinfo.file) == FAILURE)
		return (free_data(data));
	if (check_textures_validity(&data->textures) == FAILURE)
		return (print_error(ERR_INVALID_INFO) && free_data(data));
	if (check_map_validity(data, data->map) == FAILURE)
		return (print_error(ERR_INVALID_INFO) && free_data(data));
	init_player_direction(data);
	debug_display_data(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
	{
		ft_putendl_fd(ERR_WRONG_NB_ARG, 2);
		return (1);
	}
	init_data(&data);
	if (parse_args(&data, av) != 0)
		return (1);
	init_mlx(&data);
	render(&data);
	mlx_hook(data.win, EVENT_CLOSE_BTN, 0, quit_cub3d, &data);
	mlx_key_hook(data.win, key_event_handler, &data);
	mlx_loop(data.mlx);
	return (0);
}
