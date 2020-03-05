/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:35:17 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/05 14:00:44 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putmap_aux(t_data *data, t_putmap *f, int c)
{
	if (c == 1)
	{
		f->map_height = data->res_y / 5;
		f->map_width = data->res_x / 5;
		f->x = data->res_x - f->map_width;
		f->y = data->res_y - f->map_height;
		f->divider_w = (float)f->map_width / 21.0;
		f->divider_h = (float)f->map_height / 21.0;
		return ;
	}
	if (f->rel_y >= data->map_height || f->rel_y < 0
			|| f->rel_x >= data->map_width || f->rel_x < 0)
		f->color = 6579300;
	else if (f->rel_y != f->p_y || f->rel_x != f->p_x)
	{
		if ((f->aux = data->collision_map[f->rel_x][f->rel_y]))
		{
			if (f->aux == 3)
				f->color = 6579300;
			else
				f->color = f->aux == 1 ? 0 : 16711935;
		}
	}
	else
		f->color = 16711680;
}

void	ft_putmap(t_data *data)
{
	t_putmap f;

	f.p_x = (int)data->player->x;
	f.p_y = (int)data->player->y;
	f.img = (int*)data->mlx->screen_data;
	ft_putmap_aux(data, &f, 1);
	f.i = f.y - 1;
	while (++f.i < data->res_y)
	{
		f.j = f.x - 1;
		f.rel_x = f.p_x + (int)((double)(f.i - f.y) / f.divider_h) - 10;
		f.mul = f.i * data->res_x;
		while (++f.j < data->res_x)
		{
			f.color = 25;
			f.rel_y = f.p_y + (int)((double)(f.j - f.x) / f.divider_w) - 10;
			ft_putmap_aux(data, &f, 0);
			f.img[f.mul + f.j] = f.color == 25 ? f.img[f.mul + f.j] : f.color;
		}
	}
}

void	ft_lifebar(t_data *data)
{
	t_lifebar	ft;

	ft.p = data->player;
	ft.img = (int*)data->mlx->screen_data;
	ft.start_y = data->res_y / 15;
	ft.start_x = data->res_x / 15;
	ft.end_x = ft.start_x + data->res_x / 3;
	ft.end_y = ft.start_y + data->res_y / 15;
	ft.health_ptg = (ft.end_x - ft.start_x) * ft.p->health / 100 + ft.start_x;
	ft.mod_y = ft.start_y;
	while (ft.mod_y <= ft.end_y)
	{
		ft.mod_x = ft.start_x;
		while (ft.mod_x <= ft.end_x)
		{
			if (ft.mod_y == ft.start_y || ft.mod_y == ft.end_y ||
					ft.mod_x == ft.start_x || ft.mod_x == ft.end_x)
				ft.img[ft.mod_y * data->res_x + ft.mod_x] = 8355840;
			else if (ft.mod_x <= ft.health_ptg)
				ft.img[ft.mod_y * data->res_x + ft.mod_x] = 16711680;
			ft.mod_x++;
		}
		ft.mod_y++;
	}
}

void	ft_update_hud_aux(t_data *data, t_update_hud *ft)
{
	if (data->shooting)
	{
		data->shooting++;
		data->weapon_state += !(data->shooting % 10) ? 1 : 0;
		if (data->weapon_state >= 4)
		{
			data->weapon_state = 0;
			data->shooting = 0;
		}
	}
	ft->t = &data->weapon[data->weapon_state];
	ft->img = ft->t->addr;
	ft->screen_y = data->res_y - (int)data->res_y / 4;
	ft->y = 0;
	ft->screen = (int*)data->mlx->screen_data;
	ft->x_max = 2 * (int)data->res_x / 3;
	ft->x_step = (double)ft->t->width / (data->res_x / 3);
	ft->y_step = (double)ft->t->height / ((double)data->res_y / 4);
}

void	ft_update_hud(t_data *data)
{
	t_update_hud	ft;

	ft_update_hud_aux(data, &ft);
	while (ft.screen_y < data->res_y)
	{
		ft.screen_x = data->res_x / 3;
		ft.x = 0;
		while (ft.screen_x < ft.x_max)
		{
			ft.color = ft.img[(int)ft.y * (int)ft.t->width + (int)ft.x];
			if (ft.color != 9961608)
				ft.screen[ft.screen_x + data->res_x * ft.screen_y] = ft.color;
			ft.x += ft.x_step;
			ft.screen_x++;
			if (ft.x >= ft.t->width)
				ft.x = ft.t->width - 1;
		}
		ft.y += ft.y_step;
		ft.screen_y++;
		if (ft.y >= ft.t->height)
			ft.y = ft.t->height - 1;
		ft_lifebar(data);
		ft_putmap(data);
	}
}
