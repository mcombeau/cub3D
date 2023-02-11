/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexa <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:17:27 by alexa             #+#    #+#             */
/*   Updated: 2023/02/09 22:17:37 by alexa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	Checks whether the arg given is a correct .cub extension, checks that
**	 it exists and isn't a folder instead of a file.
*/

static bool	is_dir(char *arg)
{
	int		fd;
	bool	ret;

	ret = false;
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close (fd);
		ret = true;
	}
	return (ret);
}

static bool	is_cub_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'c' || arg[len - 2] != 'u'
			|| arg[len - 1] != 'b'
			|| arg[len - 4] != '.'))
		return (false);
	return (true);
}

static bool	is_xpm_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'x' || arg[len - 2] != 'p'
			|| arg[len - 1] != 'm'
			|| arg[len - 4] != '.'))
		return (false);
	return (true);
}

int	check_file(char *arg, bool cub)
{
	int	fd;

	if (is_dir(arg))
		return (err_msg(arg, ERR_FILE_IS_DIR, FAILURE));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (err_msg(arg, strerror(errno), FAILURE));
	close(fd);
	if (cub && !is_cub_file(arg))
		return (err_msg(arg, ERR_FILE_NOT_CUB, FAILURE));
	if (!cub && !is_xpm_file(arg))
		return (err_msg(arg, ERR_FILE_NOT_XPM, FAILURE));
	return (SUCCESS);
}
