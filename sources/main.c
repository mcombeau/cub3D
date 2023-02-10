/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexa <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:44:18 by alexa             #+#    #+#             */
/*   Updated: 2023/02/10 12:45:45 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_args(t_data *data, char **av)
{
	if (check_args(av[1]) == FAILURE)
		return (print_error(ERR_WRONG_FILE));
	parse_data(av[1], data);
	if (get_file_data(data, data->mapinfo.file) == FAILURE)
		return (free_data(data));
	if (check_textures_validity(&data->texinfo) == FAILURE)
		return (print_error(ERR_INVALID_INFO) && free_data(data));
	if (check_map_validity(data, data->map) == FAILURE)
		return (print_error(ERR_INVALID_INFO) && free_data(data));
	init_player_direction(data);
	if (DEBUG_MSG)
		debug_display_data(data);
	return (0);
}

static void	listen_for_input(t_data *data)
{
	mlx_hook(data->win, ClientMessage, NoEventMask, quit_cub3d, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_press_handler, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release_handler, data);
	/* mlx_hook(data->win, MotionNotify, PointerMotionMask, mouse_motion_handler, data); */
	/* mlx_hook(data->win, ButtonPress, KeyPressMask, key_press_handler, data); */
	/* mlx_hook(data->win, ButtonRelease, KeyReleaseMask, key_release_handler, data); */
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
	init_textures(&data);
	render_images(&data);
	listen_for_input(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
