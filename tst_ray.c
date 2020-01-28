/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:08:58 by eherrero          #+#    #+#             */
/*   Updated: 2020/01/28 21:43:20 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_step_calc(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->x + 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

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

t_texture	*ft_switch_texture(t_data *data, t_ray *ray)
{
	int item;

	if (ray->side == 0)
		item = ray->dir_x > 0 ? 1 : 2;
	else
		item = ray->dir_y > 0 ? 3 : 4;
	if (item == 1)
		return (data->mlx->n_img);//n
	if (item == 2)
		return (data->mlx->s_img);//s
	if (item == 3)
		return (data->mlx->e_img);//e
	return (data->mlx->w_img);//w
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

void		ft_paint_sky_col(t_ray *ray, t_data *data, t_paint_col *ft, int *img)
{
	t_texture	*t;
	float		a;
	int			i;
	int			j;
	int			offset;
	float		step;
	int			*sky_img;

	t = data->mlx->skybox;
	sky_img = t->addr;
	//printf("ray_y %f, ray_x %f\n", ray->dir_y, ray->dir_x);
	a = atan2(ray->dir_y, ray->dir_x) * 180 / M_PI + 90;
	a += a > 0 ? 0 : 360;
	//a = a > 1.57 ? 1.57 : a;
	i = 0;
	//printf("a = %f\n", a);
	//printf("h = %d\n", t->height);
	//printf("w = %d\n", t->width);

	float kk = a * t->height / 360;
	//printf("pintamos la fila %f en la columna %d\n", kk, ray->col);
	offset = t->width * (int)kk;;
	//printf("-kk-offset %d\n", offset);
	//printf("a -> %f\n", a);
	//printf("empieza a pintar\n");
	//int mod = data->res_y / t->width;	
	while (i < ft->draw_s)
	{
		j = i * t->width / data->res_y;
		//printf("pinta pixel en ray->col %d + i %d * data->res_y %d = %d\n", ray->col, i, data->res_y, ray->col + i * data->res_y);
		//printf("-pp-%d color %d\n", offset + j, sky_img[offset + j]);
		//printf("    pinta en %d la posicion %d\n", i, offset + j);
		img[ray->col + i * data->res_y] = sky_img[offset + j];
		i++;
	}
	//printf("-kk-ultimo pintado %d\n", offset + j);
	//exit(0);
}	

void		ft_paint_col(t_ray *ray, t_data *data)
{
	t_texture	*tex;
	t_paint_col	ft;
	int			*img;

	img = (int *)data->mlx->screen_data;
	ft.line_height = (int)(data->mlx->y / ray->perp_wall_dist);
	tex = ft_switch_texture(data, ray);
	ft.draw_s = -ft.line_height / 2 + data->mlx->y / 2;
	ft.draw_s = ft.draw_s < 0 ? 0 : ft.draw_s;
	ft.draw_end = ft.line_height / 2 + data->mlx->y / 2;
	if (ft.draw_end >= data->mlx->y)
		ft.draw_end = data->mlx->y - 1;
	ft.wall_x = ray->side ? data->player->x + ray->perp_wall_dist * ray->dir_x :
		data->player->y + ray->perp_wall_dist * ray->dir_y;
	ft.tex_x = ft_tex_xcalc(ray, tex, ft.wall_x);
	ft.step = 1.0 * tex->height / ft.line_height;
	ft.tex_pos = (ft.draw_s - data->mlx->y / 2 + ft.line_height / 2) * ft.step;
	ft_paint_sky_col(ray, data, &ft, img);
	while (ft.draw_s++ < ft.draw_end)
	{
		ft.tex_y = (int)ft.tex_pos & (tex->height - 1);
		ft.tex_pos += ft.step;
		ft.color = tex->addr[tex->height * ft.tex_y + ft.tex_x];
		img[ray->col + (ft.draw_s - 1) * data->res_y] = ft.color;
	}
	//exit (0);
	while (ft.draw_end < data->mlx->y)
	{
		//printf("suelo y: %d\n", y);
		//mlx_pixel_put(mlx->ptr, mlx->window, ray->col, y, 6579300);
		img[ray->col + ft.draw_end * data->res_y] = 6579300;
		ft.draw_end++;
	}
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

int			ft_render(t_data *data, t_mlx *mlx, t_player *player, int **map)
{
	t_ray	ray;
	double	camera_x;
	int		step;
	int		ray_col;

	ray_col = 0;
	while (ray_col < mlx->x)
	{
		camera_x = 2 * ray_col / (double)(mlx->x) - 1;
		ft_init_ray(&ray, player, camera_x);
		ft_step_calc(&ray, player);
		while (ray.hit == 0)
		{
			ft_ray_side_dist(&ray);
			if (map[ray.x][ray.y] > 0)
				ray.hit = 1;
		}
		ray.perp_wall_dist = ft_ray_dist(&ray, player);
		ray.col = mlx->x - ray_col;
		ft_paint_col(&ray, data);
		ray_col += 1;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->screen, 0, 0);
	return (1);
}
