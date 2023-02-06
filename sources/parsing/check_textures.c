#include "cub3d.h"

static int	check_valid_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			ft_putstr_fd("Error\nThe following number is invalid : ", 2);
			ft_putnbr_fd(rgb[i], 2);
			ft_putchar_fd('\n', 2);
			ft_putstr_fd("RGB has a min val of 0 and a max value of 255.\n", 2);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static int	check_valid_path(char *path)
{
	int	fd;
	int	len;

	fd = open(path, O_RDWR);
	len = ft_strlen(path);
	if ((path[len - 4] != '.' || path[len - 3] != 'x' || path[len - 2] != 'p'
			|| path[len - 1] != 'm'))
	{
		close(fd);
		return (FAILURE);
	}
	if (fd == -1)
	{
		close(fd);
		ft_putstr_fd("Error\nThe following path is invalid : ", 2);
		ft_putstr_fd(path, 2);
		ft_putchar_fd('\n', 2);
		return (FAILURE);
	}
	return (SUCCESS);
}

unsigned long	convert_rgb_to_hex(int *rgb_tab)
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
		|| !textures->east || !textures->floor || !textures->ceiling)
		return (FAILURE);
	if (check_valid_path(textures->north) == FAILURE
		|| check_valid_path(textures->south) == FAILURE
		|| check_valid_path(textures->west) == FAILURE
		|| check_valid_path(textures->east) == FAILURE
		|| check_valid_rgb(textures->floor) == FAILURE
		|| check_valid_rgb(textures->ceiling) == FAILURE)
		return (FAILURE);
	textures->hex_floor = convert_rgb_to_hex(textures->floor);
	textures->hex_ceiling = convert_rgb_to_hex(textures->ceiling);
	return (SUCCESS);
}