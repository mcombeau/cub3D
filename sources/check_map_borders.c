#include "cub3d.h"

int	check_top_or_bottom(char **map_tab, int i, int j)
{
	while (map_tab[i][j] == ' ' || map_tab[i][j] == '\t'
	|| map_tab[i][j] == '\r' || map_tab[i][j] == '\v'
	|| map_tab[i][j] == '\f')
		j++;
	while (map_tab[i][j])
	{
		if (map_tab[i][j] != '1')
			return (FAILURE);
		j++;
	}
	return (SUCCESS);
}

int	check_map_sides(t_mapinfo *map, char **map_tab)
{
	int	i;
	int	j;

	if (check_top_or_bottom(map_tab, 0, 0) == FAILURE)
		return (FAILURE);
	i = 1;
	while (i < (map->height - 1))
	{
		j = ft_strlen(map_tab[i]) - 1;
		if (map_tab[i][j] != '1')
			return (FAILURE);
		i++;
	}
	if (check_top_or_bottom(map_tab, i, 0) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	check_left_side_is_closed(char **map_tab)
{
	int	i;
	int	j;

	j = 0;
	i = skip_walls(map_tab);
	while (map_tab[i][j] && (is_a_white_space(map_tab[i][j]) == SUCCESS
		|| map_tab[i][j] == '1'))
		j++;
	if (map_tab[i - 1][j] != '1')
		return (FAILURE);
	while (map_tab[i] && ft_strchr(map_tab[i], '0'))
	{
		j = 0;
		while (map_tab[i][j] && (is_a_white_space(map_tab[i][j]) == SUCCESS
			|| ft_strchr("1NSEW", map_tab[i][j])))
			j++;
		if (is_a_white_space(map_tab[i - 1][j]) == SUCCESS
			|| is_a_white_space(map_tab[i + 1][j]) == SUCCESS)
			return (FAILURE);
		if (!ft_strchr("1NSEW", map_tab[i][j - 1]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

static int	check_first_line_on_right_side(char **map_tab, int *index)
{
	int	i;
	int	j;

	i = 0;
	while (map_tab[i])
	{
		j = 0;
		while (map_tab[i][j]
			&& (is_a_white_space(map_tab[i][j]) == SUCCESS
			|| map_tab[i][j] == '1'))
			j++;
		if (map_tab[i][j] == '0')
			break ;
		i++;
	}
	j = ft_strlen(map_tab[i]) - 1;
	while (map_tab[i][j] && (is_a_white_space(map_tab[i][j]) == SUCCESS
		|| map_tab[i][j] == '1'))
		j--;
	if (((int)ft_strlen(map_tab[i - 1]) - 1 < j - 1)
		|| (map_tab[i - 1][j] != '1'))
		return (FAILURE);
	*index = i + 1;
	return (SUCCESS);
}

int	check_right_side_is_closed(char **map_tab)
{
	int	i;
	int	j;

	i = 0;
	if (check_first_line_on_right_side(map_tab, &i) == FAILURE)
		return (FAILURE);
	while (map_tab[i] && ft_strchr(map_tab[i], '0'))
	{
		j = ft_strlen(map_tab[i]) - 1;
		while (map_tab[i][j] && (is_a_white_space(map_tab[i][j]) == SUCCESS
			|| ft_strchr("1NSEW", map_tab[i][j])))
			j--;
		if (ft_strlen(map_tab[i - 1]) - 1 < (size_t)j
			|| is_a_white_space(map_tab[i - 1][j]) == SUCCESS)
			return (FAILURE);
		if (ft_strlen(map_tab[i + 1]) - 1 < (size_t)j
			|| is_a_white_space(map_tab[i + 1][j]) == SUCCESS)
			return (FAILURE);
		if (!ft_strchr("1NSEW", map_tab[i][j + 1]))
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}