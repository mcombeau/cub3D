#include "cub3d.h"

void	debug_print_char_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	debug_display_data(t_data *data)
{
	debug_print_char_tab(data->map);
	printf("\nMap height: %d\n", data->mapinfo.height);
	printf("Map width: %d\n", data->mapinfo.width);
	printf("\tNorth: %f\n", data->mapinfo.north);
	printf("\tEast: %f\n", data->mapinfo.east);
	printf("\tSouth: %f\n", data->mapinfo.south);
	printf("\tWest: %f\n", data->mapinfo.west);

	printf("\nPlayer position: x = %d, y = %d\n", data->player.tile_x, data->player.tile_y);
	printf("Player direction: %c\n", data->player.direction);
	printf("Player view angle: %f\n", data->player.view_angle);
	printf("Index end of map: %d\n", data->mapinfo.index_end_of_map);
}
