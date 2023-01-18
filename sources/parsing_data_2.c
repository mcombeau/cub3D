#include "cub3d.h"

int	count_map_lines(t_data *data, char **map_infos, int i)
{
	int index_value;
	int	j;

	index_value = i;
	while (map_infos[i])
	{
		j = 0;
		while (map_infos[i][j] == ' ' || map_infos[i][j] == '\t' || map_infos[i][j] == '\r'
		|| map_infos[i][j] == '\v' || map_infos[i][j] == '\f')
			j++;
		if (map_infos[i][j] != '1')
			break;
		i++;
	}
	data->map.index_end_of_map = i;
	return (i - index_value);
}

int	fill_map_tab(t_map *map, char **map_tab, int index)
{
	int i;

	i = 0;
	while (i < map->nb_line)
	{
		map_tab[i] = ft_strdup(map->map_infos[index]);
		if (!map_tab[i])
			return (FAILURE);
		if (map_tab[i][ft_strlen(map_tab[i]) - 1] == '\n')
			map_tab[i][ft_strlen(map_tab[i]) - 1] = '\0';
		i++;
		index++;
	}
	return (SUCCESS);
}

void	change_space_into_wall(t_map *map)
{
	int i;
	int j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j] == ' ' || map->map[i][j] == '\t' || map->map[i][j] == '\r'
		|| map->map[i][j] == '\v' || map->map[i][j] == '\f')
			j++;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == ' ' && j != map->map[i][ft_strlen(map->map[i]) - 1])
				map->map[i][j] = '1';
		}
		i++;
	}
}

int	get_only_map(t_data *data, char **map_infos, int i)
{
	data->map.nb_line = count_map_lines(data, map_infos, i);
	data->map.map = malloc(sizeof(char *) * data->map.nb_line + 1);
	if (!data->map.map)
		return (FAILURE);
	if (fill_map_tab(&data->map, data->map.map, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int	parse_map_description(t_data *data, char **map_infos, int i)
{
	if (get_only_map(data, map_infos, i) == FAILURE)
		return (FAILURE);
	change_space_into_wall(&data->map);
	for (int i = 0; data->map.map[i]; i++)
		printf("*: %s\n", data->map.map[i]);
	
	return (SUCCESS);
}