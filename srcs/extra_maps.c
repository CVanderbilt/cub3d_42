/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:37:52 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/04 11:55:07 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_reset_arrow_map(t_data *data)
{
	int		i;
	int		j;
	t_arrow	**a_map;

	a_map = data->arrow_map;
	i = -1;
	while (++i < data->map_height)
	{
		j = -1;
		while (++j < data->map_width)
			(&a_map[i][j])->used = 0;
	}
}

void	ft_set_surrounding(t_data *d, t_coordinate *c, int index, int *arrows)
{
	int				x;
	int				y;
	t_try_params	t;

	x = c[index].x;
	y = c[index].y;
	t.data = d;
	t.x = x;
	t.y = y;
	ft_set_etile(&t, arrows, c);
	t.x = x;
	t.y = y;
	ft_set_stile(&t, arrows, c);
	t.x = x;
	t.y = y;
	ft_set_wtile(&t, arrows, c);
	t.x = x;
	t.y = y;
	ft_set_ntile(&t, arrows, c);
}

void	ft_update_arrow_map(t_data *data)
{
	int				i;
	int				arrows;
	t_arrow			**a_map;
	t_coordinate	history[data->map_height * data->map_width];

	a_map = data->arrow_map;
	history[0].x = (int)data->player->x;
	history[0].y = (int)data->player->y;
	(&a_map[(int)data->player->x][(int)data->player->y])->y = 0;
	(&a_map[(int)data->player->x][(int)data->player->y])->x = 0;
	i = 0;
	arrows = 1;
	ft_reset_arrow_map(data);
	while (i < arrows)
	{
		ft_set_surrounding(data, history, i, &arrows);
		i++;
	}
}

void	ft_update_extra_maps(t_data *data)
{
	t_sprite	*s;
	int			**c_map;
	int			y;
	int			x;

	c_map = data->collision_map;
	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width)
			c_map[y][x] = data->map[y][x];
	}
	y = -1;
	s = data->sprite_buffer;
	while (++y < data->sprites_num)
	{
		c_map[(int)s[y].x][(int)s[y].y] = 2;
	}
	ft_update_arrow_map(data);
}
