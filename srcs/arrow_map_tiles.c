/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_map_tiles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:39:43 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/03 14:59:47 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_try(t_try_params *p)
{
	t_arrow *s;

	if (p->x < 0 || p->y < 0 ||
			p->x >= p->data->map_height || p->y >= p->data->map_width)
		return (0);
	s = &p->data->arrow_map[p->x][p->y];
	if (!s->used)
	{
		s->used = 1;
		p->data->arrow_map[p->x][p->y].dir_x = p->dir_x;
		s->dir_y = p->dir_y;
		if (p->data->collision_map[p->x][p->y])
			return (0);
		return (1);
	}
	return (0);
}

void	ft_set_etile(t_try_params *p, int *arrows, t_coordinate *c)
{
	p->dir_x = 1;
	p->dir_y = 0;
	p->x -= 1;
	if (ft_try(p))
	{
		{
			(&c[*arrows])->x = p->x;
			(&c[*arrows])->y = p->y;
			*arrows += 1;
		}
	}
}

void	ft_set_stile(t_try_params *p, int *arrows, t_coordinate *c)
{
	p->dir_x = 0;
	p->dir_y = 1;
	p->y -= 1;
	if (ft_try(p))
	{
		{
			(&c[*arrows])->x = p->x;
			(&c[*arrows])->y = p->y;
			*arrows += 1;
		}
	}
}

void	ft_set_wtile(t_try_params *p, int *arrows, t_coordinate *c)
{
	p->dir_x = -1;
	p->dir_y = 0;
	p->x += 1;
	if (ft_try(p))
	{
		{
			(&c[*arrows])->x = p->x;
			(&c[*arrows])->y = p->y;
			*arrows += 1;
		}
	}
}

void	ft_set_ntile(t_try_params *p, int *arrows, t_coordinate *c)
{
	p->dir_x = 0;
	p->dir_y = -1;
	p->y += 1;
	if (ft_try(p))
	{
		{
			(&c[*arrows])->x = p->x;
			(&c[*arrows])->y = p->y;
			*arrows += 1;
		}
	}
}
