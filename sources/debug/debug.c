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
}
