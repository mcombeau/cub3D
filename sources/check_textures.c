#include "cub3d.h"

static int	check_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			ft_putstr_fd("The following number is invalid : ", 2);
			ft_putnbr_fd(rgb[i], 2);
			ft_putchar_fd('\n', 2);
			ft_putstr_fd("RGB has a min value of 0 and a max value of 255.\n", 2);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static int	check_path_exist(char *path)
{
	int	fd;

	fd = open(path, O_RDWR);
	if (fd == -1)
	{
		close(fd);
		ft_putstr_fd("The following path is invalid : ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
		return (FAILURE);
	}
	return (SUCCESS);
}	

int	check_info_retrieved(t_textures *texture)
{
	if (!texture->dir_NO || !texture->dir_SO || !texture->dir_WE 
	|| !texture->dir_EA || !texture->floor || !texture->ceiling)
		return (FAILURE);
	if (check_path_exist(texture->dir_NO) == FAILURE
		|| check_path_exist(texture->dir_SO) == FAILURE
		|| check_path_exist(texture->dir_WE) == FAILURE
		|| check_path_exist(texture->dir_EA) == FAILURE
		|| check_rgb(texture->floor) == FAILURE
		|| check_rgb(texture->ceiling) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}