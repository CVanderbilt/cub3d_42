/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 14:57:41 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/03 15:02:14 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_init_ray(t_ray *ray, t_player *player, double camera_x)
{
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
	ray->x = (int)(player->x);
	ray->y = (int)(player->y);
	ray->hit = 0;
	ray->side = 0;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ft_step_calc(ray, player);
}

void		ft_paint_sky_col(t_ray *ray, t_data *d, t_paint_col *ft, int *img)
{
	t_paint_sky_col	f;

	f.t = d->mlx->skybox;
	f.sky_img = f.t->addr;
	f.a = atan2(ray->dir_y, ray->dir_x) * 180 / M_PI + 90;
	f.a += f.a > 0 ? 0 : 360;
	f.i = 0;
	f.kk = f.a * f.t->height / 360;
	if (f.kk >= f.t->height)
		f.kk = f.t->height - 1;
	f.offset = f.t->width * (int)f.kk;
	while (f.i < ft->draw_s)
	{
		f.j = f.i * f.t->width / d->res_y;
		img[ray->col + f.i * d->res_x] = f.sky_img[f.offset + f.j];
		f.i++;
	}
}

void		ft_paint_col(t_ray *ray, t_data *data)
{
	t_paint_col	ft;

	ft.img = (int *)data->mlx->screen_data;
	ft.line_height = (int)(data->mlx->y / ray->perp_wall_dist);
	ft.tex = ft_switch_texture(data, ray);
	ft.draw_s = -ft.line_height / 2 + data->mlx->y / 2;
	ft.draw_s = ft.draw_s < 0 ? 0 : ft.draw_s;
	ft.draw_end = (ft.line_height) / 2 + data->mlx->y / 2;
	ft.draw_end = ft.draw_end >= data->mlx->y ? data->mlx->y - 1 : ft.draw_end;
	ft.wall_x = ray->side ? data->player->x + ray->perp_wall_dist * ray->dir_x :
		data->player->y + ray->perp_wall_dist * ray->dir_y;
	ft.tex_x = ft_tex_xcalc(ray, ft.tex, ft.wall_x);
	ft.step = 1.0 * ft.tex->height / ft.line_height;
	ft.tex_pos = (ft.draw_s - data->mlx->y / 2 + ft.line_height / 2) * ft.step;
	ft_paint_sky_col(ray, data, &ft, ft.img);
	ft.mul = (ft.tex->height) * ft.tex_x;
	while (ft.draw_s++ < ft.draw_end)
	{
		ft.tex_y = (int)ft.tex_pos & ((int)ft.tex->height - 1);
		ft.tex_pos += ft.step;
		ft.color = ft.tex->addr[ft.mul + ft.tex_y];
		ft.img[ray->col + (ft.draw_s - 1) * data->res_x] = ft.color;
	}
	while (ft.draw_end++ < data->mlx->y)
		ft.img[ray->col + (ft.draw_end - 2) * data->res_x] = data->floor_color;
}
