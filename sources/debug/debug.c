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
	printf("\nPlayer position: x = %d, y = %d\n", data->player.x, data->player.y);
	printf("Player direction: %c\n", data->player.direction);
	printf("Index end of map: %d\n", data->mapinfo.index_end_of_map);
}
