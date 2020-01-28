/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:53:37 by eherrero          #+#    #+#             */
/*   Updated: 2020/01/28 19:22:27 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_key_release_hook(int keycode, void *params)
{
	printf("released keycode: %d\n", keycode);
	ft_check_movement((t_data *)params, keycode, 0);
	return (0);
}

void	ft_print_states(t_player *player)
{
	printf("mov forward: %d\n", player->moving_forward);
	printf("mov backward: %d\n", player->moving_backward);
}

void	ft_check_movement(t_data *data, int keycode, int state)
{
	printf(" state: %d\n", state);
	printf(" keycode: %d\n", keycode);
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
	ft_print_states(data->player);
}

int		ft_player_advance(t_data *data, int code, double step)
{
	t_player	*p;
	int			mod;

	mod = code == 1 || code == 3 ? -1 : 1;
	p = data->player;
	if (code == 0 || code == 1)
	{
		if (!data->map[(int)(p->x + mod * p->dir_x * step)][(int)(p->y)])
			p->x += mod * p->dir_x * step;
		if (!data->map[(int)(p->x)][(int)(p->y + mod * p->dir_y * step)])
			p->y += mod * p->dir_y * step;
	}
	else if (code == 2 || code == 3)
	{
		if (!data->map[(int)(p->x - mod * p->dir_y * step)][(int)(p->y)])
			p->x -= mod * p->dir_y * step;
		if (!data->map[(int)(p->x)][(int)(p->y + mod * p->dir_x * step)])
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
	if (moved)
	{
		printf("(x, y) (%f, %f)\n", player->x, player->y);
		printf("dir(x, y) (%f, %f)\n", player->dir_x, player->dir_y);
		printf("plane_x %f plane_y %f\n", player->plane_x, player->plane_y);
	}
	return (moved);
}

int		ft_loop_hook(void *params)
{
	t_data	*data;
	t_mlx	*mlx;
	int		moved;
	static int frame;

	data = (t_data *)params;
	mlx = data->mlx;
	moved = ft_move(data, data->player);
	//mlx_clear_window(mlx->ptr, mlx->window);
	if (moved)
	{
		printf("RENDER_START %d\n", frame);
		ft_render(data, data->mlx, data->player, data->map);
	}
	frame++;
	return (0);
}

int		ft_key_hook(int keycode, void *params)
{
	printf("pressed keycode: %d\n", keycode);
	ft_check_movement((t_data *)params, keycode, 1);
	return (0);
}
