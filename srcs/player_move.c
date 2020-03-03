/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:42:01 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/03 15:00:21 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_movement(t_data *data, int keycode, int state)
{
	if (keycode == 13)
		data->player->moving_forward = state;
	if (keycode == 1)
		data->player->moving_backward = state;
	if (keycode == 124)
		data->player->rotating_left = state;
	if (keycode == 123)
		data->player->rotating_right = state;
	if (keycode == 0)
		data->player->moving_right = state;
	if (keycode == 2)
		data->player->moving_left = state;
}

int		ft_can_walk(t_data *data, int x, int y)
{
	t_sprite	*s;
	int			i;

	i = 0;
	s = data->sprite_buffer;
	while (i < data->sprites_num)
	{
		if ((int)s[i].x == x && (int)s[i].y == y)
			return (0);
		i++;
	}
	return (1);
}

int		ft_player_advance(t_data *data, int code, double step)
{
	t_player	*p;
	int			mod;

	mod = code == 1 || code == 3 ? -1 : 1;
	p = data->player;
	if (code == 0 || code == 1)
	{
		if (!data->collision_map[(int)(p->x + mod * p->dir_x * step)]
				[(int)p->y])
			p->x += mod * p->dir_x * step;
		if (!data->collision_map[(int)p->x]
				[(int)(p->y + mod * p->dir_y * step)])
			p->y += mod * p->dir_y * step;
	}
	else if (code == 2 || code == 3)
	{
		if (!data->collision_map[(int)(p->x - mod * p->dir_y * step)]
				[(int)p->y])
			p->x -= mod * p->dir_y * step;
		if (!data->collision_map[(int)p->x]
				[(int)(p->y + mod * p->dir_x * step)])
			p->y += mod * p->dir_x * step;
	}
	return (1);
}

int		ft_player_rotate(t_player *player, double a, int code)
{
	if (code)
		a *= -1;
	player->x2 = player->dir_x;
	player->dir_x = player->dir_x * cos(a) - player->dir_y * sin(a);
	player->dir_y = player->x2 * sin(a) + player->dir_y * cos(a);
	player->x2 = player->plane_x;
	player->plane_x = player->plane_x * cos(a) - player->plane_y * sin(a);
	player->plane_y = player->x2 * sin(a) + player->plane_y * cos(a);
	return (1);
}

int		ft_move(t_data *data, t_player *player)
{
	double	step;
	double	a;
	int		moved;

	moved = 0;
	step = player->mov_speed;
	a = player->rot_speed;
	if (player->moving_forward)
		moved += ft_player_advance(data, 0, step);
	if (player->moving_backward)
		moved += ft_player_advance(data, 1, step);
	if (player->moving_right)
		moved += ft_player_advance(data, 2, step);
	if (player->moving_left)
		moved += ft_player_advance(data, 3, step);
	if (player->rotating_right)
		moved += ft_player_rotate(player, a, 0);
	if (player->rotating_left)
		moved += ft_player_rotate(player, a, 1);
	return (moved);
}
