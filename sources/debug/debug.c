#include "cub3d.h"

void	debug_display_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map.map[i])
	{
		printf("%s\n", data->map.map[i]);
		i++;
	}
}

void	debug_display_data(t_data *data)
{
	debug_display_map(data);
	printf("Map nb_line: %d\n", data->map.nb_line);
	printf("\nPlayer position: x = %d, y = %d\n", data->map.p_x, data->map.p_y);
	printf("Player direction: %c\n", data->map.p_direction);
	printf("Index end of map: %d\n", data->map.index_end_of_map);
}
