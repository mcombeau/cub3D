#include "cub3d.h"

static int		get_minimap_offset(int mapsize, int pos)
{
	if (pos > MMAP_VIEW_DIST && mapsize - pos > MMAP_VIEW_DIST + 1)
		return (pos - MMAP_VIEW_DIST);
	if (pos > MMAP_VIEW_DIST && mapsize - pos <= MMAP_VIEW_DIST + 1)
		return (mapsize - MMAP_SIZE + 1);
	return (0);
}

static int	is_valid_map_coord(int coord, int size)
{
	if (coord < size)
		return (1);
	return (0);
}

static char	*add_minimap_line(t_data *data, int offset_x, int offset_y, int y)
{
	char	*line;
	int		x;

	line = ft_calloc(MMAP_SIZE + 1, sizeof * line);
	if (!line)
		return (NULL);
	x = 0;
	while (x < MMAP_SIZE && x < data->mapinfo.width)
	{
		if (!is_valid_map_coord(y + offset_y, data->mapinfo.height)
			|| !is_valid_map_coord(x + offset_x, data->mapinfo.width))
			line[x] = ' ';
		else if (data->player.x == (x + offset_x)
			&& data->player.y == (y + offset_y))
			line[x] = 'P';
		else if (data->map[y + offset_y][x + offset_x] == '1')
			line[x] = '1';
		else if (ft_strchr("0NSEW", data->map[y + offset_y][x + offset_x]))
			line[x] = '0';
		else
			line[x] = ' ';
		x++;
	}
	return (line);
}

static char	**generate_minimap(t_data *data, int offset_x, int offset_y)
{
	char	**minimap;
	int		y;

	minimap = ft_calloc(MMAP_SIZE + 1, sizeof * minimap);
	if (!minimap)
		return (NULL);
	y = 0;
	while (y < MMAP_SIZE && y < data->mapinfo.height)
	{
		minimap[y] = add_minimap_line(data, offset_x, offset_y, y);
		if (!minimap[y])
		{
			free_tab(minimap);
			return (NULL);
		}
		y++;
	}
	return (minimap);
}

void	render_minimap(t_data *data)
{
	char	**minimap;
	int		offset_x;
	int		offset_y;

	offset_x = get_minimap_offset(data->mapinfo.width, data->player.x);
	offset_y = get_minimap_offset(data->mapinfo.height, data->player.y);
	minimap = generate_minimap(data, offset_x, offset_y);
	if (!minimap)
		return ;
	debug_print_char_tab(minimap);
	render_minimap_image(data, minimap);
	free_tab(minimap);
}


