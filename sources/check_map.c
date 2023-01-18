#include "cub3d.h"

static int	check_map_elements(t_map *map, char **map_tab)
{
	int	i;
	int	j;

	i = 0;
	map->player_dir = '0';
	while (map_tab[i])
	{
		j = 0;
		while (map_tab[i][j])
		{
			while (map->map[i][j] == ' ' || map->map[i][j] == '\t' || map->map[i][j] == '\r'
			|| map->map[i][j] == '\v' || map->map[i][j] == '\f')
				j++;
			if (!(ft_strchr("10NSEW", map_tab[i][j])))
				return (print_error("There is an invalid letter in the map"));
			if (ft_strchr("NSEW", map_tab[i][j]) && map->player_dir != '0')
				return (print_error("There is more than one player position"));
			if (ft_strchr("NSEW", map_tab[i][j]) && map->player_dir == '0')
				map->player_dir = map_tab[i][j];
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

static int	check_position_is_valid(t_map *map, char **map_tab)
{
	int i;
	int j;

	i = map->player_y;
	j = map->player_x;
	if (ft_strlen(map_tab[i - 1]) < (size_t)j
		|| ft_strlen(map_tab[i + 1]) < (size_t)j
		|| is_a_white_space(map_tab[i][j - 1]) == SUCCESS
		|| is_a_white_space(map_tab[i][j + 1]) == SUCCESS
		|| is_a_white_space(map_tab[i - 1][j]) == SUCCESS
		|| is_a_white_space(map_tab[i + 1][j]) == SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

static int	check_player_position(t_map *map, char **map_tab)
{
	int	i;
	int j;

	if (map->player_dir == '0')
		return (print_error("The map should have a player_direction"));
	i = 0;
	while (map_tab[i])
	{
		j = 0;
		while (map_tab[i][j])
		{
			if (ft_strchr("NSEW", map_tab[i][j]))
			{
				map->player_x = j;
				map->player_y = i;
			}
			j++;
		}
		i++;
	}
	if (check_position_is_valid(map, map_tab) == FAILURE)
		return (print_error("Player position is invalid"));
	return (SUCCESS);
}

static int	check_map_is_at_the_end(t_map *map)
{
	int	i;
	int j;

	i = map->index_end_of_map;
	while (map->map_infos[i])
	{
		j = 0;
		while (map->map_infos[i][j])
		{
			if (map->map_infos[i][j] != ' ' && map->map_infos[i][j] != '\t' && map->map_infos[i][j] != '\r'
			&& map->map_infos[i][j] != '\n' && map->map_infos[i][j] != '\v' && map->map_infos[i][j] != '\f')
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	check_map(t_map *map, char **map_tab)
{
	if (map->nb_line < 3)
		return (print_error("The map should be at least 3 lines long."));
	if (check_map_elements(map, map_tab) == FAILURE)
		return (FAILURE);
	if (check_map_sides(map, map_tab) == FAILURE)
		return (print_error("The map must be surrounded by walls"));
	if (check_left_side_is_closed(map_tab) == FAILURE)
		return (print_error("The map is not fully closed"));
	if (check_right_side_is_closed(map_tab) == FAILURE)
		return (print_error("RIGHT The map is not fully closed"));
	if (check_player_position(map, map_tab) == FAILURE)
		return (FAILURE);
	if (check_map_is_at_the_end(map) == FAILURE)
		return (print_error("The map description is not the last element"));
	return (SUCCESS);
}