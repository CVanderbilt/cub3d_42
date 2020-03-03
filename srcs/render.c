/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:56:27 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/03 16:23:17 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_step_calc_2(t_ray *ray, double x, double y)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (x - ray->x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->x + 1.0 - x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (y - ray->y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->y + 1.0 - y) * ray->delta_dist_y;
	}
}

void		ft_step_calc(t_ray *ray, t_player *player)
{
	ft_step_calc_2(ray, player->x, player->y);
}

double		ft_ray_dist(t_ray *ray, t_player *player)
{
	if (ray->side)
		return ((ray->y - player->y + (1 - ray->step_y) / 2) / ray->dir_y);
	return ((ray->x - player->x + (1 - ray->step_x) / 2) / ray->dir_x);
}

void		ft_ray_side_dist(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->y += ray->step_y;
		ray->side = 1;
	}
}

void		ft_render(t_data *data, t_mlx *mlx, t_player *player, int **map)
{
	t_ray	ray;
	double	camera_x;
	int		ray_col;

	ray_col = -1;
	while (++ray_col < data->res_x)
	{
		camera_x = 2 * ray_col / (double)(mlx->x) - 1;
		ft_init_ray(&ray, player, camera_x);
		ft_step_calc(&ray, player);
		while (!ray.hit)
		{
			ft_ray_side_dist(&ray);
			if (map[ray.x][ray.y] > 0)
				ray.hit = 1;
		}
		ray.perp_wall_dist = ft_ray_dist(&ray, player);
		data->buffer_z[ray_col] = ray.perp_wall_dist;
		ray.col = mlx->x - ray_col;
		ft_paint_col(&ray, data);
	}
	ft_paint_sprites(data);
	ft_update_hud(data);
	if (data->screenshot)
		take_screenshot(data);
}
