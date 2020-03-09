/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_paint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:00:20 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/09 14:21:49 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	*ft_get_sprite_texture(t_data *data, t_sprite *s)
{
	t_gst	ft;

	ft.p = data->player;
	ft.t = &data->sprite_tex_buffer[s->texture];
	ft.t->offset = s->texture >= data->sprite_tex_num ? ft_cub_error() : 0;
	if (s->type == 0 || s->type == 2)
		return (ft.t);
	ft.sector = 360 / ft.t->a_directions;
	ft.a = ((atan2(s->dir_y, s->dir_x) * 180 / M_PI + 90)
			- (atan2(ft.p->dir_y, ft.p->dir_x) * 180 / M_PI + 90));
	ft.x_grid = ft_get_gridx(ft.a);
	if (s->shoot)
	{
		ft.t = data->soldier_shoot;
		if (s->shoot < 25)
			ft.t->offset = 0;
		else
			ft.t->offset = s->shoot < 60 ? ft.t->width : ft.t->width * 2;
		return (ft.t);
	}
	else
		ft.t = s->state == 1 ? ft_select_moving_tex(data) : data->soldier_anim;
	ft.x_grid += ft.x_grid <= 3 ? 4 : -4;
	ft.t->offset = (int)(ft.x_grid * ft.t->width);
	return (ft.t);
}

void		ft_paint_one_sprite_aux(t_data *data, t_sprite *sprite, t_pos *f)
{
	f->screen = (int*)data->mlx->screen_data;
	if (sprite->type == 3)
		f->t = data->void_sprite;
	else
		f->t = ft_get_sprite_texture(data, sprite);
	f->img = f->t->addr;
	f->p = data->player;
	f->s_x = sprite->x - f->p->x;
	f->s_y = sprite->y - f->p->y;
	f->i_t = 1.0 / (f->p->plane_x * f->p->dir_y - f->p->plane_y * f->p->dir_x);
	f->tf_x = f->i_t * (f->p->dir_y * f->s_x - f->p->dir_x * f->s_y);
	f->tf_y = f->i_t * (-f->p->plane_y * f->s_x + f->p->plane_x * f->s_y);
	f->ss_x = (int)((data->res_x / 2) * (1 + f->tf_x / f->tf_y));
	f->sprite_h = abs((int)(data->res_y / f->tf_y));
	f->start_y = -(f->sprite_h) / 2 + data->res_y / 2;
	f->start_y = f->start_y < 0 ? 0 : f->start_y;
	f->end_y = f->sprite_h / 2 + data->res_y / 2;
	f->end_y = f->end_y >= data->res_y ? data->res_y - 1 : f->end_y;
	f->s_w = abs((int)(data->res_y / f->tf_y));
	f->start_x = -f->s_w / 2 + f->ss_x;
	f->start_x = f->start_x < 0 ? 0 : f->start_x;
	f->end_x = f->s_w / 2 + f->ss_x;
	f->end_x = f->end_x >= data->res_x ? data->res_x - 1 : f->end_x;
	f->c = f->start_x - 1;
}

void		ft_paint_one_sprite(t_data *data, t_sprite *sprite)
{
	t_pos f;

	ft_paint_one_sprite_aux(data, sprite, &f);
	while (++f.c < f.end_x)
	{
		f.t_x = (int)(256 * (f.c - (-f.s_w / 2 + f.ss_x))
				* f.t->width / f.s_w) / 256;
		f.t_x = f.t_x >= f.t->width ? f.t->width - 1 : f.t_x;
		f.t_x = f.t_x < 0 ? 0 : f.t_x;
		f.y = f.start_y - 1;
		if (f.tf_y > 0 && f.c > 0 && f.c < data->res_x &&
				f.tf_y < data->buffer_z[f.c])
			while (++f.y < f.end_y)
			{
				f.d = (f.y) * 256 - data->res_y * 128 + f.sprite_h * 128;
				f.t_y = ((f.d * f.t->height) / f.sprite_h) / 256;
				f.t_y = f.t_y >= f.t->height ? f.t->height - 1 : f.t_y;
				f.t_y = f.t_y < 0 ? 0 : f.t_y;
				f.col = f.img[f.t->offset + f.t->real_width * f.t_y + f.t_x];
				if (f.col != 9961608)
					f.screen[f.y * data->res_x + data->res_x - f.c] = ft_redder(
							f.col, f.tf_y);
			}
	}
}

void		ft_sort_sprites(int *orden, double *dist, int num)
{
	int		i;
	int		aux_i;
	double	aux_d;
	int		sorted;

	sorted = 0;
	while (!sorted)
	{
		i = -1;
		sorted = 1;
		while (++i < num - 1)
		{
			if (dist[i] < dist[i + 1])
			{
				aux_i = orden[i];
				orden[i] = orden[i + 1];
				orden[i + 1] = aux_i;
				aux_d = dist[i];
				dist[i] = dist[i + 1];
				dist[i + 1] = aux_d;
				sorted = 0;
			}
		}
	}
}

void		ft_paint_sprites(t_data *data)
{
	int			orden[data->sprites_num];
	double		distancias[data->sprites_num];
	t_player	*p;
	t_sprite	*sprite;
	int			i;

	p = data->player;
	sprite = data->sprite_buffer;
	i = -1;
	while (++i < data->sprites_num)
	{
		orden[i] = i;
		distancias[i] = ((p->x - sprite[i].x) * (p->x - sprite[i].x)
				+ (p->y - sprite[i].y) * (p->y - sprite[i].y));
	}
	ft_sort_sprites(orden, distancias, data->sprites_num);
	i = 0;
	while (i < data->sprites_num)
	{
		ft_paint_one_sprite(data, sprite + orden[i]);
		i++;
	}
}
