/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:40:35 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/03 15:00:36 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_sprite_advance(t_data *data, int code, double step, t_sprite *s)
{
	float	new_x;
	float	new_y;

	code = 1;
	new_x = s->x + s->dir_x * step;
	new_y = s->y + s->dir_y * step;
	if (((int)new_x == (int)s->x && (int)new_y == (int)s->y) ||
			!data->collision_map[(int)new_x][(int)new_y])
	{
		s->x = new_x;
		s->y = new_y;
	}
}

void	ft_activate_sprite(t_data *data, t_sprite *s)
{
	int i;

	i = -1;
	while (++i < data->sprites_num)
	{
		if (s->type == 1 && s->state == 0)
		{
			if (fabs(data->player->x - s->x) + fabs(data->player->y - s->y) < 5)
				s->state = 1;
		}
	}
}

void	ft_move_soldiers(t_data *d)
{
	int					i;
	t_sprite			*s;
	double				f_x;
	double				f_y;
	t_try_shoot_params	param;

	i = -1;
	while (++i < d->sprites_num)
	{
		s = &d->sprite_buffer[i];
		if (s->type == 1)
		{
			f_x = s->x - (int)s->x;
			f_y = s->y - (int)s->y;
			ft_init_ts_param(d, s, &param);
			if (ft_try_shoot(&param))
				ft_shoot_succes(d, s);
			else
				ft_shoot_fail(d, s, f_x, f_y);
		}
	}
}

int		ft_is_soldier(t_data *data, int x, int y)
{
	int			i;
	t_sprite	s;

	i = -1;
	while (++i < data->sprites_num)
	{
		s = data->sprite_buffer[i];
		if (s.type == 1)
		{
			if ((int)s.x == x && (int)s.y == y)
				return (1);
		}
	}
	return (0);
}
