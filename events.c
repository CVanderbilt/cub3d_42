/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:53:37 by eherrero          #+#    #+#             */
/*   Updated: 2020/01/31 19:22:04 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_key_release_hook(int keycode, void *params)
{
//	printf("released keycode: %d\n", keycode);
	ft_check_movement((t_data *)params, keycode, 0);
	return (0);
}

void	ft_print_states(t_player *player)
{
//	printf("mov forward: %d\n", player->moving_forward);
//	printf("mov backward: %d\n", player->moving_backward);
}

void	ft_check_movement(t_data *data, int keycode, int state)
{
//	printf(" state: %d\n", state);
//	printf(" keycode: %d\n", keycode);
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
	double		safe_step;


	mod = code == 1 || code == 3 ? -1 : 1;
	safe_step =1; // mod * 0.001;
	p = data->player;
	if (code == 0 || code == 1)
	{
		if (ft_can_walk(data, (int)(p->x + mod * p->dir_x * step), (int)p->y))
			if (!data->map[(int)(p->x + mod * (p->dir_x) * step)][(int)(p->y)])
				p->x += mod * p->dir_x * step;
		if (ft_can_walk(data, (int)p->x, (int)p->y + mod * p->dir_y * step))
			if (!data->map[(int)(p->x)][(int)(p->y + mod * (p->dir_y * safe_step) * step)])
			p->y += mod * p->dir_y * step;
	}
	else if (code == 2 || code == 3)
	{
		if (!data->map[(int)(p->x - mod * p->dir_y * step)][(int)(p->y)])
			if (ft_can_walk(data, (int)p->x - mod * p->dir_y * step, (int)p->y))
				p->x -= mod * p->dir_y * step;
		if (!data->map[(int)(p->x)][(int)(p->y + mod * p->dir_x * step)])
			if (ft_can_walk(data, (int)p->x, (int)p->y + mod * p->dir_x * step))
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
	//printf("entra a ft_moive\n");
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
		/*
		printf("(x, y) (%f, %f)\n", player->x, player->y);
		printf("dir(x, y) (%f, %f)\n", player->dir_x, player->dir_y);
		printf("plane_x %f plane_y %f\n", player->plane_x, player->plane_y);
		//ft_render(data, data->mlx, data->player, data->map);*/
	}
	return (moved);
}

int		ft_loop_hook(void *params)
{
//	printf("???\n");
	t_data	*data;
	t_mlx	*mlx;
	int		moved;
	static int frame;

//	printf("loophook_star\n");
	data = (t_data *)params;
	t_player	*player = data->player; 
	mlx = data->mlx;
	moved = ft_move(data, data->player);
	//mlx_clear_window(mlx->ptr, mlx->window);
//	if (moved)
	{
		//printf("RENDER_START %d\n", frame);
		//printf("(x, y) (%f, %f)\n", player->x, player->y);
		//printf("dir(x, y) (%f, %f)\n", player->dir_x, player->dir_y);
		//printf("plane_x %f plane_y %f\n", player->plane_x, player->plane_y);
		if ((player->dir_x == 1 || player->dir_x == -1) ||
			(player->dir_y == 1 || player->dir_y == -1))
			{
			//	printf("ha corregido\n");
				ft_player_rotate(player, player->rot_speed - 0.001, 0);
			}
//		printf("start_render\n");
		ft_render(data, data->mlx, data->player, data->map);
//		printf("render_completed\n");
	}
	frame++;
	return (0);
}

void	ft_free_map(t_data *data)
{
	int i;

	i = 0;
	while (i < data->map_height)
	{
		free (data->map[i]);
		i++;
	}
	free (data->map);
}

void	ft_free_texture(t_data *data, t_texture *t)
{
	//printf("  free %p\n", t->addr);
//	free(t->addr);
	mlx_destroy_image(data->mlx->ptr, t->img);
//	free(t->img);
	//printf("  free(ft_free_texture)%p\n", t);
	free(t);
	//printf("sin problemas\n");
}

void	ft_free_textures(t_data *data)
{
	//printf("  free %p\n", data->n_texture);
	free(data->n_texture);
	//printf("  free %p\n", data->s_texture);
	free(data->s_texture);
	//printf("  free %p\n", data->e_texture);
	free(data->e_texture);
	//printf("  free %p\n", data->w_texture);
	free(data->w_texture);
	ft_free_texture(data, data->mlx->n_img);
	ft_free_texture(data, data->mlx->s_img);
	ft_free_texture(data, data->mlx->e_img);
	ft_free_texture(data, data->mlx->w_img);
	ft_free_texture(data, data->mlx->skybox);
}

void	ft_free_sprite(t_data *data, t_sprite *sprite)
{
	ft_free_texture(data, sprite->texture);
	//printf("  free %p\n", sprite->texture_path);
	free(sprite->texture_path);
	//free(sprite);
}

void	ft_free_sprites(t_data *data)
{
	int			i;
	t_sprite	*s;

	i = 0;
	s = data->sprite_buffer;
	//free(s);
	while (i < data->sprites_num)
	{
		ft_free_sprite(data, s + i);
//		printf("liberta: %d\n", i);
		i++;
	}
	//printf("  free(ft_free_sprites) %p\n", s);
	free(s);
	//printf("sin problema\n");
}

void	ft_free_mlx(t_mlx *mlx)
{
	//printf("  free -1- >%p<\n", mlx->title);
//	free(mlx->title);
//	printf("2\n");
	mlx_destroy_image(mlx->ptr, mlx->screen);
//	printf("3\n");
	mlx_destroy_window(mlx->ptr, mlx->window);
//	printf("4\n");
	//free(mlx->ptr);
	//free(mlx);
	//free(mlx->screen_data);
}

int		ft_key_hook(int keycode, void *params)
{
//	printf("pressed keycode: %d\n", keycode);
	t_data *data;

	data = (t_data*)params;
	if (keycode == 53)
	{
		ft_free_map(data);
	//	mlx_destroy_image(data->mlx->ptr, data->img);
	//	free(data->img);
	//	printf("  free %p\n", data->buffer_z);
		free(data->buffer_z);
		ft_free_textures(data);
		ft_free_sprites(data);
	//	printf("  free %p\n", data->player);
		free(data->player);
		ft_free_mlx(data->mlx);
////////getchar();
		exit(0);
	}
	ft_check_movement((t_data *)params, keycode, 1);
	return (0);
}
