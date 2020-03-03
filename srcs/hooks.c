/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:33:49 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/03 15:00:12 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_key_release_hook(int keycode, void *params)
{
	ft_check_movement((t_data *)params, keycode, 0);
	return (0);
}

int		ft_loop_hook(void *params)
{
	t_data		*data;
	t_player	*player;
	t_mlx		*mlx;
	int			moved;

	data = (t_data *)params;
	player = data->player;
	mlx = data->mlx;
	moved = ft_move(data, data->player);
	{
		if ((player->dir_x == 1 || player->dir_x == -1) ||
			(player->dir_y == 1 || player->dir_y == -1))
			ft_player_rotate(player, player->rot_speed - 0.001, 0);
		ft_render(data, data->mlx, data->player, data->map);
		ft_lifebar(data);
		mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->screen, 0, 0);
		data->animation_num++;
		ft_update_extra_maps(data);
		ft_move_soldiers(data);
		if (data->animation_num >= data->animation_cycle)
			data->animation_num = 0;
	}
	return (0);
}

int		ft_key_hook(int keycode, void *params)
{
	int		y;
	t_data	*data;

	data = (t_data*)params;
	y = -1;
	if (keycode == 126)
		if (!data->shooting)
			data->shooting++;
	if (keycode == 53)
		ft_free_and_exit(data);
	ft_check_movement(data, keycode, 1);
	return (0);
}
