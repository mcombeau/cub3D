/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:31:14 by mcombeau          #+#    #+#             */
/*   Updated: 2023/02/09 11:31:16 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player_north_south(t_player *player)
{
	if (player->direction == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (player->direction == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else
		return ;
}

void	init_player_east_west(t_player *player)
{
	if (player->direction == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	else if (player->direction == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	else
		return ;
}

void	init_player_direction(t_data *data)
{
	init_player_north_south(&data->player);
	init_player_east_west(&data->player);
}
