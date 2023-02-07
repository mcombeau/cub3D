#include "cub3d.h"

/*
We initialize the set up for the rays
- camera_x -> Where is the camera (-1 = left, 0 = center, 1 = right)
- raydir_x/y = direction of the ray
- mapx/y = current square of the ray
- deltadist_x/y = distance to go to the next x or y.
*/

static void	init_raycasting_info(int x, t_ray *ray, t_player *player)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->raydir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->raydir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->mapx = (int)player->pos_x;
	ray->mapy = (int)player->pos_y;
	ray->deltadist_x = fabs(1 / ray->raydir_x);
	ray->deltadist_y = fabs(1 / ray->raydir_y);
}

/*
- We are doing the initial set up for the dda
- dda algorithm will jump one square in each loop eiter in a x or y direction
- ray->sidedist_x or y = distance from the ray start position to the
	next x or y position
- if x or y < 0 go the next x or y to the left
- if x or y > 0 go the next x or y to the right
*/

static void	set_dda(t_ray *ray, t_player *player)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player->pos_x - ray->mapx) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->mapx + 1.0 - player->pos_x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player->pos_y - ray->mapy) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->mapy + 1.0 - player->pos_y) * ray->deltadist_y;
	}
}

/*
- We implement the DDA algorithm -> the loop will increment 1 square until we hit a wall
- If the sidedistx < sidedisty, x is the closest point from the ray
*/

static void	perform_dda(t_ray *ray, t_player *player, char **map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->mapx += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->mapy += ray->step_y;
			ray->side = 1;
		}
		if (map[ray->mapy][ray->mapx] == '1')
			hit = 1;
	}
	if (ray->side == 0)
		ray->wall_dist = (ray->mapx - player->pos_x + (1 - ray->step_x) / 2) / ray->raydir_x;
	else
		ray->wall_dist = (ray->mapy - player->pos_y + (1 - ray->step_y) / 2) / ray->raydir_y;
}


static void	calculate_line_height(t_ray *ray, t_data *data, t_player *player)
{
	ray->line_height = (int)(data->win_height / ray->wall_dist);
	ray->draw_start = -(ray->line_height) / 2 + data->win_height / 2;
	ray->draw_end = ray->line_height / 2 + data->win_height / 2;
	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;
	if (ray->side == 0)
	{
		ray->wall_x = player->pos_y + ray->wall_dist * ray->raydir_y;
		if (ray->raydir_x > 0)
			data->texinfo.index = NORTH;
		else
			data->texinfo.index = SOUTH;
	}
	else
	{
		ray->wall_x = player->pos_x + ray->wall_dist * ray->raydir_x;
		if (ray->raydir_y > 0)
			data->texinfo.index = WEST;
		else
			data->texinfo.index = EAST;
	}
	ray->wall_x -= floor(ray->wall_x);
}

int	raycasting(t_player *player, t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	ray = data->ray;
	while (x++ < WIN_WIDTH)
	{
		init_ray(&ray);
		init_raycasting_info(x, &ray, player);
		set_dda(&ray, player);
		perform_dda(&ray, player, data->map);
		calculate_line_height(&ray, data, player);
		update_texture_pixels(data, &data->texinfo, &ray, x);
	}
	return (SUCCESS);
}
