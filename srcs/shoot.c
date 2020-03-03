/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:43:27 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/03 15:00:29 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	ft_init_shoot_ray(t_ray *ray, t_try_shoot_params *p)
{
	double magnitude;

	ray->x = p->x;
	ray->y = p->y;
	ray->dir_x = p->x_dest - p->x;
	ray->dir_y = p->y_dest - p->y;
	magnitude = sqrt(ray->dir_x * ray->dir_x + ray->dir_y * ray->dir_y);
	ray->dir_x /= magnitude;
	ray->dir_y /= magnitude;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ft_step_calc_2(ray, p->x, p->y);
	return (magnitude);
}

int		ft_try_shoot(t_try_shoot_params *p)
{
	t_ray	ray;
	double	magnitude;

	magnitude = ft_init_shoot_ray(&ray, p);
	if (fabs(atan2(p->x_dir, p->y_dir) - atan2(ray.dir_x, ray.dir_y)) > 0.8 ||
			magnitude > 8)
		return (0);
	while (1)
	{
		ft_ray_side_dist(&ray);
		if ((int)ray.x >= p->d->map_height || (int)ray.x < 0 ||
			(int)ray.y >= p->d->map_width || (int)ray.y < 0 ||
			p->d->collision_map[ray.x][ray.y])
			return (0);
		else if ((int)ray.x == (int)p->d->player->x &&
				(int)ray.y == (int)p->d->player->y)
			return (1);
	}
	return (0);
}

void	ft_shoot_succes(t_data *d, t_sprite *s)
{
	if (s->state == 1)
	{
		s->shoot++;
		if (s->shoot == 75)
		{
			s->shoot = 25;
			d->player->health--;
		}
	}
	else
		s->state = 1;
}

void	ft_shoot_fail(t_data *d, t_sprite *s, double f_x, double f_y)
{
	s->shoot = 0;
	if (s->state == 1)
	{
		if (f_x >= 0.2 && f_y >= 0.2 && f_x <= 0.8 && f_y <= 0.8)
		{
			s->dir_x = d->arrow_map[(int)(s->x)][(int)(s->y)].dir_x;
			s->dir_y = d->arrow_map[(int)(s->x)][(int)(s->y)].dir_y;
		}
		ft_sprite_advance(d, 0, d->player->mov_speed / 2, s);
	}
}

void	ft_init_ts_param(t_data *d, t_sprite *s, t_try_shoot_params *p)
{
	p->d = d;
	p->x_dir = s->dir_x;
	p->y_dir = s->dir_y;
	p->x = s->x;
	p->y = s->y;
	p->x_dest = d->player->x;
	p->y_dest = d->player->y;
}
