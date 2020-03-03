/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_assets.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:05:55 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/03 16:35:25 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_player(t_player *player, double r_speed, double m_speed)
{
	player->x = 0;
	player->y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->rot_speed = r_speed;
	player->mov_speed = m_speed;
	player->health = 100;
	player->ammo = 8;
	player->move_them = 0;
	player->moving_forward = 0;
	player->moving_backward = 0;
	player->moving_left = 0;
	player->moving_right = 0;
	player->rotating_right = 0;
	player->rotating_left = 0;
}

void	ft_init_mlx(t_data *data, char *map_name)
{
	t_mlx	*mlx;
	int		bpp;
	int		e;
	int		size_line;

	e = 1;
	bpp = 4;
	size_line = data->res_x * 4;
	mlx = data->mlx;
	mlx->x = data->res_x > 0 ? data->res_x : 500;
	mlx->y = data->res_y > 0 ? data->res_y : 500;
	mlx->screen = mlx_new_image(mlx->ptr, mlx->x, mlx->y);
	mlx->screen_data = mlx_get_data_addr(mlx->screen, &bpp, &size_line, &e);
	ft_init_textures(data);
	if (!mlx->ptr)
		ft_memory_error();
	if (!(mlx->window = mlx_new_window(mlx->ptr, mlx->x, mlx->y, map_name)))
		ft_memory_error();
}

void	ft_init_extra_maps(t_data *data)
{
	int		**c_map;
	t_arrow	**a_map;
	int		i;
	int		j;

	i = -1;
	c_map = (int**)malloc(sizeof(int*) * data->map_height);
	a_map = (t_arrow**)malloc(sizeof(t_arrow*) * data->map_height);
	if (!a_map || !c_map)
		ft_memory_error();
	while (++i < data->map_height)
	{
		c_map[i] = (int*)malloc(sizeof(int) * data->map_width);
		a_map[i] = (t_arrow*)malloc(sizeof(t_arrow) * data->map_width);
		if (!c_map[i] || !a_map[i])
			ft_memory_error();
		j = -1;
		while (++j < data->map_width)
			a_map[i][j].used = 0;
	}
	data->collision_map = c_map;
	data->arrow_map = a_map;
}

void	ft_init_data(t_data *d, char *map, double rsp, double msp)
{
	t_player	*player;
	t_mlx		*mlx;

	d->weapon_state = 0;
	d->shooting = 0;
	d->animation_num = 0;
	d->animation_cycle = 48;
	player = (t_player*)malloc(sizeof(t_player));
	mlx = (t_mlx*)malloc(sizeof(t_mlx));
	if (!player || !mlx)
		ft_memory_error();
	mlx->ptr = mlx_init();
	d->player = player;
	d->mlx = mlx;
	ft_init_player(player, rsp, msp);
	d->sprite_buffer = 0;
	d->sprites_num = 0;
	d->sprite_tex_buffer = 0;
	d->sprite_tex_num = 0;
	ft_get_map(map, d);
	d->buffer_z = (double*)malloc(d->res_x * sizeof(double));
	if (!d->buffer_z)
		ft_memory_error();
	ft_init_mlx(d, map);
	ft_init_extra_maps(d);
}

void	ft_loop(t_data *data)
{
	t_mlx *mlx;

	mlx = data->mlx;
	mlx_hook(mlx->window, 2, 1, ft_key_hook, data);
	mlx_hook(mlx->window, 3, 0, ft_key_release_hook, data);
	mlx_hook(mlx->window, 17, 0, ft_free_and_exit, data);
	mlx_loop_hook(mlx->ptr, ft_loop_hook, data);
	mlx_loop(mlx->ptr);
}
