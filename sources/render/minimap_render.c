/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcombeau <mcombeau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 11:29:15 by mcombeau          #+#    #+#             */
/*   Updated: 2023/02/09 12:29:37 by mcombeau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_mmap_offset(t_minimap *minimap, int mapsize, int pos)
{
	if (pos > minimap->view_dist && mapsize - pos > minimap->view_dist + 1)
		return (pos - minimap->view_dist);
	if (pos > minimap->view_dist && mapsize - pos <= minimap->view_dist + 1)
		return (mapsize - minimap->size);
	return (0);
}

static bool	is_valid_map_coord(int coord, int size)
{
	if (coord < size)
		return (true);
	return (false);
}

static char	*add_minimap_line(t_data *d, t_minimap *m, int y)
{
	char	*line;
	int		x;

	line = ft_calloc(m->size + 1, sizeof * line);
	if (!line)
		return (NULL);
	x = 0;
	while (x < m->size && x < d->mapinfo.width)
	{
		if (!is_valid_map_coord(y + m->offset_y, d->mapinfo.height)
			|| !is_valid_map_coord(x + m->offset_x, d->mapinfo.width))
			line[x] = '\0';
		else if ((int)d->player.pos_x == (x + m->offset_x)
			&& (int)d->player.pos_y == (y + m->offset_y))
			line[x] = 'P';
		else if (d->map[y + m->offset_y][x + m->offset_x] == '1')
			line[x] = '1';
		else if (d->map[y + m->offset_y][x + m->offset_x] == '0')
			line[x] = '0';
		else
			line[x] = '\0';
		x++;
	}
	return (line);
}

static char	**generate_minimap(t_data *data, t_minimap *minimap)
{
	char	**mmap;
	int		y;

	mmap = ft_calloc(minimap->size + 1, sizeof * mmap);
	if (!mmap)
		return (NULL);
	y = 0;
	while (y < minimap->size && y < data->mapinfo.height)
	{
		mmap[y] = add_minimap_line(data, minimap, y);
		if (!mmap[y])
		{
			free_tab((void **)mmap);
			return (NULL);
		}
		y++;
	}
	return (mmap);
}

void	render_minimap(t_data *data)
{
	t_minimap	minimap;

	minimap.map = NULL;
	minimap.img = &data->minimap;
	minimap.view_dist = MMAP_VIEW_DIST;
	minimap.size = (2 * minimap.view_dist) + 1;
	minimap.tile_size = MMAP_PIXEL_SIZE / (2 * minimap.view_dist);
	minimap.offset_x = get_mmap_offset(&minimap,
			data->mapinfo.width, (int)data->player.pos_x);
	minimap.offset_y = get_mmap_offset(&minimap,
			data->mapinfo.height, (int)data->player.pos_y);
	minimap.map = generate_minimap(data, &minimap);
	if (!minimap.map)
	{
		err_msg(NULL, ERR_MALLOC, 0);
		return ;
	}
	if (MMAP_DEBUG_MSG)
		debug_display_minimap(&minimap);
	render_minimap_image(data, &minimap);
	free_tab((void **)minimap.map);
}
