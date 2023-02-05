#include "cub3d.h"

void	debug_print_char_tab(char **tab)
{
	int	i;

	printf("\n");
	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	printf("\n");
}

void	debug_display_minimap(t_minimap *minimap)
{
	printf(YELLOW "\n---- MINIMAP\n" RESET);
	printf("Minimap view distance: %d\n", minimap->view_dist);
	printf("Minimap size: %d * %d\n", minimap->size, minimap->size);
	debug_print_char_tab(minimap->map);
}

void	debug_display_data(t_data *data)
{
	printf(YELLOW "\n---- MAP\n" RESET);
	printf("Map height: %d\n", data->mapinfo.height);
	printf("Map width: %d\n", data->mapinfo.width);
	debug_print_char_tab(data->map);
	printf("- North: %f\n", data->mapinfo.north);
	printf("- East: %f\n", data->mapinfo.east);
	printf("- South: %f\n", data->mapinfo.south);
	printf("- West: %f\n", data->mapinfo.west);

	printf(YELLOW "\n---- PLAYER\n" RESET);
	printf("Player tile: ");
	printf("x = %d, y = %d\n", data->player.tile_x, data->player.tile_y);
	printf("Player pos: ");
	printf("x = %f, y = %f\n", data->player.pos_x, data->player.pos_y);
	printf("Player direction: %c ", data->player.direction);
	printf("(x = %f, y = %f)\n", data->player.dir_x, data->player.dir_y);
	printf("Player view angle: %f\n", data->player.view_angle);
	printf("\n");
}
