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

int	check_args(char *arg)
{
	size_t	len;
	int		fd;

	len = ft_strlen(arg);
	fd = open(arg, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (FAILURE);
	}
	else
	{
		fd = open(arg, O_RDONLY);
		close(fd);
		if ((arg[len - 3] != 'c' || arg[len - 2] != 'u'
				|| arg[len - 1] != 'b'
				|| arg[len - 4] != '.') || fd < 0)
			return (FAILURE);
		else
			return (SUCCESS);
	}
}
