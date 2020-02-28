/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_selector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:58:42 by eherrero          #+#    #+#             */
/*   Updated: 2020/02/25 15:00:03 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	*ft_switch_texture(t_data *data, t_ray *ray)
{
	int item;

	if (ray->side == 0)
		item = ray->dir_x > 0 ? 1 : 2;
	else
		item = ray->dir_y > 0 ? 3 : 4;
	if (item == 1)
		return (data->mlx->n_img);
	if (item == 2)
		return (data->mlx->s_img);
	if (item == 3)
		return (data->mlx->e_img);
	return (data->mlx->w_img);
}

int			ft_tex_xcalc(t_ray *ray, t_texture *tex, double wall_x)
{
	int ret;

	ret = (int)(((wall_x - floor(wall_x)) * (double)(tex->width)));
	if (!ray->side && ray->dir_x > 0)
		ret = tex->width - ret - 1;
	if (ray->side && ray->dir_y < 0)
		ret = tex->width - ret - 1;
	return (ret);
}

int			ft_get_gridx(double a)
{
	double	sector;

	sector = 360 / 8;
	a += sector / 2;
	if ((int)(a * 10) >= 0)
		return ((int)(a / sector));
	a *= -1;
	return (7 - (int)(a / sector));
}

int			ft_get_gridy(t_data *data, t_sprite *s, int states)
{
	int n;

	if (!s->moved)
		return (0);
	n = data->animation_cycle / (states - 1);
	return (data->animation_num / n + 1);
}

t_texture	*ft_select_moving_tex(t_data *data)
{
	int n;

	n = data->animation_cycle / 4;
	n = data->animation_num / n + 1;
	return (&data->soldier_anim[n]);
	if (n == 0)
		return (&data->soldier_anim[1]);
	if (n == 1)
		return (&data->soldier_anim[2]);
	if (n == 2)
		return (&data->soldier_anim[3]);
	if (n == 3)
		return (&data->soldier_anim[4]);
	return (&data->soldier_anim[0]);
}
