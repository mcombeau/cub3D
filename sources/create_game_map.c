#include "cub3d.h"

int	count_map_lines(t_data *data, char **file, int i)
{
	int	index_value;
	int	j;

	index_value = i;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\r'
		|| file[i][j] == '\v' || file[i][j] == '\f')
			j++;
		if (file[i][j] != '1')
			break ;
		i++;
	}
	data->map.index_end_of_map = i;
	return (i - index_value);
}

int	fill_map_tab(t_map *map, char **map_tab, int index)
{
	int		i;
	int		j;
	size_t	biggest_len;

	biggest_len = find_biggest_len(map, index);
	i = 0;
	while (i < map->nb_line)
	{
		j = 0;
		map_tab[i] = malloc(sizeof(char) * (biggest_len + 1));
		if (!map_tab[i])
			return (FAILURE);
		while (map->file[index][j] && map->file[index][j] != '\n')
		{
			map_tab[i][j] = map->file[index][j];
			j++;
		}	
		while (j < (int)biggest_len)
			map_tab[i][j++] = '\0';
		i++;
		index++;
	}
	map_tab[i] = NULL;
	return (SUCCESS);
}

int	get_map_info(t_data *data, char **file, int i)
{
	data->map.nb_line = count_map_lines(data, file, i);
	data->map.map = malloc(sizeof(char *) * (data->map.nb_line + 1));
	if (!data->map.map)
		return (FAILURE);
	if (fill_map_tab(&data->map, data->map.map, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

void	change_space_into_wall(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j] == ' ' || map->map[i][j] == '\t'
		|| map->map[i][j] == '\r'
		|| map->map[i][j] == '\v' || map->map[i][j] == '\f')
			j++;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == ' '
				&& j != map->map[i][ft_strlen(map->map[i]) - 1])
				map->map[i][j] = '1';
		}
		i++;
	}
}

int	create_map(t_data *data, char **file, int i)
{
	if (get_map_info(data, file, i) == FAILURE)
		return (FAILURE);
	change_space_into_wall(&data->map);
	return (SUCCESS);
}