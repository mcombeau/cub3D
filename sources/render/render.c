/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:30:04 by mcombeau          #+#    #+#             */
/*   Updated: 2023/02/12 13:45:01 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_frame_image_pixel(t_data *data, t_img *image, int x, int y)
{
	if (data->texture_pixels[y][x] > 0)
		set_image_pixel(image, x, y, data->texture_pixels[y][x]);
	else if (y < data->win_height / 2)
		set_image_pixel(image, x, y, data->texinfo.hex_ceiling);
	else if (y < data->win_height -1)
		set_image_pixel(image, x, y, data->texinfo.hex_floor);
}

static void	render_frame(t_data *data)
{
	t_img	image;
	int		x;
	int		y;

	image.img = NULL;
	init_img(data, &image, data->win_width, data->win_height);
	y = 0;
	while (y < data->win_height)
	{
		x = 0;
		while (x < data->win_width)
		{
			set_frame_image_pixel(data, &image, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, image.img, 0, 0);
	mlx_destroy_image(data->mlx, image.img);
}

static void	render_raycast(t_data *data)
{
	init_texture_pixels(data);
	init_ray(&data->ray);
	raycasting(&data->player, data);
	render_frame(data);
}

void	render_images(t_data *data)
{
	render_raycast(data);
	if (BONUS)
		render_minimap(data);
}

int	render(t_data *data)
{
	data->player.has_moved += move_player(data);
	if (data->player.has_moved == 0)
		return (0);
	render_images(data);
	return (0);
}
