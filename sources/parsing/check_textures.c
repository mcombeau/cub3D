/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexa <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:29:02 by alexa             #+#    #+#             */
/*   Updated: 2023/02/09 22:29:05 by alexa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_valid_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
			return (err_msg_val(rgb[i], ERR_TEX_RGB_VAL, FAILURE));
		i++;
	}
	return (SUCCESS);
}

// static int	check_valid_path(char *path)
// {
// 	int	fd;
// 	int	len;

// 	fd = open(path, O_RDWR);
// 	len = ft_strlen(path);
// 	if ((path[len - 4] != '.' || path[len - 3] != 'x' || path[len - 2] != 'p'
// 			|| path[len - 1] != 'm'))
// 	{
// 		close(fd);
// 		return (err_msg(path, ERR_FILE_NOT_XPM, FAILURE));
// 	}
// 	if (fd == -1)
// 	{
// 		close(fd);
// 		ft_putstr_fd("Error\nThe following path is invalid : ", 2);
// 		ft_putstr_fd(path, 2);
// 		ft_putchar_fd('\n', 2);
// 		return (FAILURE);
// 	}
// 	close(fd);
// 	return (SUCCESS);
// }

static unsigned long	convert_rgb_to_hex(int *rgb_tab)
{
	unsigned long	result;
	int				r;
	int				g;
	int				b;

	r = rgb_tab[0];
	g = rgb_tab[1];
	b = rgb_tab[2];
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

int	check_textures_validity(t_texinfo *textures)
{
	if (!textures->north || !textures->south || !textures->west
		|| !textures->east)
		return (err_msg(NULL, ERR_TEX_MISSING, FAILURE));
	if (!textures->floor || !textures->ceiling)
		return (err_msg(NULL, ERR_COLOR_MISSING, FAILURE));
	if (check_file(textures->north, false) == FAILURE
		|| check_file(textures->south, false) == FAILURE
		|| check_file(textures->west, false) == FAILURE
		|| check_file(textures->east, false) == FAILURE
		|| check_valid_rgb(textures->floor) == FAILURE
		|| check_valid_rgb(textures->ceiling) == FAILURE)
		return (FAILURE);
	textures->hex_floor = convert_rgb_to_hex(textures->floor);
	textures->hex_ceiling = convert_rgb_to_hex(textures->ceiling);
	return (SUCCESS);
}
