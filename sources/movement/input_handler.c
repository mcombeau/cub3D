/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:31:03 by mcombeau          #+#    #+#             */
/*   Updated: 2023/02/10 12:43:38 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		quit_cub3d(data);
	if (key == XK_Left)
		data->player.rotate -= 1;
	if (key == XK_Right)
		data->player.rotate += 1;
	if (key == XK_w)
		data->player.move_y = 1;
	if (key == XK_a)
		data->player.move_x = -1;
	if (key == XK_s)
		data->player.move_y = -1;
	if (key == XK_d)
		data->player.move_x = 1;
	return (0);
}

int	key_release_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		quit_cub3d(data);
	if (key == XK_w && data->player.move_y == 1)
		data->player.move_y = 0;
	if (key == XK_s && data->player.move_y == -1)
		data->player.move_y = 0;
	if (key == XK_a && data->player.move_x == -1)
		data->player.move_x += 1;
	if (key == XK_d && data->player.move_x == 1)
		data->player.move_x -= 1;
	if (key == XK_Left && data->player.rotate <= 1)
		data->player.rotate = 0;
	if (key == XK_Right && data->player.rotate >= -1)
		data->player.rotate = 0;
	return (0);
}

int	mouse_motion_handler(int x, int y, t_data *data)
{
	static int	old_x = 0;

	printf("old x = %d, x = %d\n", old_x, x);
	if (old_x == 0)
		old_x = x;
	if (x == old_x)
	{
		old_x = x;
		return (0);
	}
	else if (x < old_x && x < data->win_width / 2)
	{
		/* data->player.rotate -= 1; */
		data->player.has_moved += rotate_player(data, -1);
		old_x = x;
	}
	else if (x > old_x && x > data->win_width / 2)
	{
		/* data->player.rotate += 1; */
		data->player.has_moved += rotate_player(data, 1);
		old_x = x;
	}
	old_x = x;
	(void)y;
	return (0);
}
