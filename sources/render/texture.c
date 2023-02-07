#include "cub3d.h"

void	init_texture_pixels(t_data *data)
{
	int	i;

	if (data->texture_pixels)
		free_tab((void **)data->texture_pixels);
	data->texture_pixels = ft_calloc(data->win_height + 1,
			sizeof * data->texture_pixels);
	if (!data->texture_pixels)
		clean_exit(data, msg("cub3d: %s\n", "malloc error.", 1));
	i = 0;
	while (i < data->win_height)
	{
		data->texture_pixels[i] = ft_calloc(data->win_width + 1,
				sizeof * data->texture_pixels);
		if (!data->texture_pixels[i])
			clean_exit(data, msg("cub3d: %s\n", "malloc error.", 1));
		i++;
	}
}

void	update_texture_pixels(t_data *data, t_texinfo *tex, t_ray *ray, int x)
{
	int			y;
	int			color;

	tex->x = (int)(ray->wall_x * tex->size);
	if ((ray->side == 0 && ray->raydir_x > 0)
		|| (ray->side == 1 && ray->raydir_y < 0))
		tex->x = tex->size - tex->x - 1;
	tex->step = 1.0 * tex->size / ray->line_height;
	tex->pos = (ray->draw_start - data->win_height / 2
			+ ray->line_height / 2) * tex->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->y = (int)tex->pos & (tex->size - 1);
		tex->pos += tex->step;
		color = data->textures[tex->index][tex->size * tex->y + tex->x];
		/* color = 0x00FF00; */
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		if (color > 0)
			data->texture_pixels[y][x] = color;
		++y;
	}
}
