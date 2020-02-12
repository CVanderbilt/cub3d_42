/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:53:37 by eherrero          #+#    #+#             */
/*   Updated: 2020/02/12 18:52:28 by eherrero         ###   ########.fr       */
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

void	ft_sprite_advance(t_data *data, int code, double step, t_sprite *s)
{
	int		mod;

	mod = code == 1 || code == 3 ? -1 : 0;
	//printf("sprite advance");
	if (code == 0 || code == 1)
	{
//		printf(" if(1)");
		//if (ft_can_walk(data, (int)(s->x + mod * s->dir_x * step), (int)s->y))
		//	if (!data->map[(int)(s->x + mod * (s->dir_x) * step)][(int)(s->y)])
			{
//				printf(" if(2) x = %f", s->x);
				s->x += mod * s->dir_x * step;
//				printf(" -> %f", s->x);
			}
		//if (ft_can_walk(data, (int)s->x, (int)s->y + mod * s->dir_y * step))
		//	if (!data->map[(int)(s->x)][(int)(s->y + mod * (s->dir_y) * step)])
			{
//				printf(" if(3) y = %f", s->y);
				s->y += mod * s->dir_y * step;
//				printf(" -> %f", s->y);
			}
	}
//	printf(" \n");
}

int		ft_player_advance(t_data *data, int code, double step)
{
	t_player	*p;
	int			mod;


	mod = code == 1 || code == 3 ? -1 : 1;
	p = data->player;
	if (code == 0 || code == 1)
	{
			//printf("intenta %d (x) (%d, %d); ", data->collision_map[(int)p->y][(int)(p->x + mod * p->dir_x * step)],
	//		(int)p->y, (int)(p->x + mod * p->dir_x * step));
		//if (data->collision_map[(int)p->y][(int)(p->x + mod * p->dir_x * step)] == 0)
		if (!data->collision_map[(int)(p->x + mod * p->dir_x * step)][(int)p->y])
		{
			//printf("avanza a x -> %f\n", p->x + mod *p->dir_x * step);
			p->x += mod * p->dir_x * step;
		}
		//else
		//	printf("ha intentado %d (x)  ", data->collision_map[(int)p->y][(int)(p->x + mod * p->dir_x * step)]);
		//printf("intenta %d (y) (%d, %d) ", data->collision_map[(int)(p->y + mod * p->dir_y * step)][(int)p->x],
		//	(int)(p->y + mod * p->dir_y * step), (int)p->x);
		//if (data->collision_map[(int)(p->y + mod * p->dir_y * step)][(int)p->x] == 0)
		if (!data->collision_map[(int)p->x][(int)(p->y + mod * p->dir_y * step)])
		{
			//printf("avanza a y -> %f\n", p->y + mod *p->dir_y * step);
			p->y += mod * p->dir_y * step;
		}
		//else
	//		printf("ha intentado %d (y)  ", data->collision_map[(int)(p->y + mod * p->dir_y * step)][(int)p->x]  );

	}
	else if (code == 2 || code == 3)
	{
		if (!data->collision_map[(int)(p->x - mod * p->dir_y * step)][(int)p->y])
			p->x -= mod * p->dir_y * step;
		if (!data->collision_map[(int)p->x][(int)(p->y + mod * p->dir_x * step)])
			p->y += mod * p->dir_x * step;
	}
//	printf("pos x,y (%d, %d) map: %d c_map %d\n", (int)p->x, (int)p->y, data->map[(int)p->x][(int)p->y],
//			data->collision_map[(int)p->x][(int)p->y]);
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

void	ft_move_soldiers(t_data *data)
{
	int			i;
	int			test_order;
	t_sprite	*s;
	double		f_x;
	double		f_y;
	int mod;

	i = 0;
	//test_order = data->player->move_them;
	//if (!data->player->move_them)
	//	return ;
	while (i < data->sprites_num)
	{
		s = &data->sprite_buffer[i];
		if (s->type == 1)
		{
		//	printf("sprite s %d, pos %f %f\n", i, s->x, s->y);
			f_x = s->x - (int)s->x;
			f_y = s->y - (int)s->y;
		//	printf("f_x %f f_y %f\n", f_x, f_y);
			if (f_x >= 0.4 && f_y >= 0.4 && f_x <= 0.6 && f_y <= 0.6)
			{
				mod = !(data->collision_map[(int)s->x][(int)s->y]) ? -1 : 1;
				s->dir_x = mod * data->arrow_map[(int)round(s->x)][(int)round(s->y)].dir_x;//	if (
				s->dir_y = mod * data->arrow_map[(int)round(s->x)][(int)round(s->y)].dir_y;//	if (
			}
			//exit(0);
		}
		ft_sprite_advance(data, 0, data->player->mov_speed / 10, s);
	//	printf("dir_x %f, dir_y %f p_dir_x %f, p_dir_y %f\n", s->dir_x, s->dir_y, data->player->dir_x, data->player->dir_y);
		//exit(0);
		s->x += data->player->mov_speed * 1 / 4 * s->dir_x;
		s->y += data->player->mov_speed * 1 / 4 * s->dir_y;
		i++;
	}
}

int		ft_try(t_data *data, int dir_x, int dir_y, int x, int y)
{
	t_arrow *s;

//	printf("try %d %d dir %d %d\n", x, y, dir_x, dir_y);
	if (x < 0 || y < 0 || x >= data->map_height || y >= data->map_width)
	{
		printf("x: %d y: %d\n", x, y);
		return (0);
	}
	s = &data->arrow_map[x][y];
	if (!s->used)
	{
	//	printf("set %d %d with %d %d\n", x, y, dir_x, dir_y);
		s->used = 1;
		data->arrow_map[x][y].dir_x = dir_x;
		s->dir_y = dir_y;
		if (data->collision_map[x][y])
		{
//			printf("  collide\n");
			return (0);
		}
		return (1);
	}
//	printf("  used\n");
	return (0);
}

void	ft_set_surrounding(t_data *data, t_coordinate *c, int index, int *arrows)
{
	int		**c_map;
	t_arrow	***a_map;
	int		x;
	int		y;
	int r;
	t_coordinate *p;

	c_map = data->collision_map;
	a_map = &data->arrow_map;
	x = c[index].x;
	y = c[index].y;
	//set e 0 a 4 arrows apuntando a (x, y)
	//printf("start surroundings of (%d, %d) arrows %d\n", x, y, *arrows);
//	printf("set surroundings of %d %d, with dir %d %d\n", x, y, data->arrow_map[x][y].dir_x, data->arrow_map[x][y].dir_y);
	if ((ft_try(data, 1, 0, x - 1, y)))
	{
//		printf("  set  %d %d with %d %d\n", x - 1, y, (*a_map)[x - 1][y].dir_x, (*a_map)[x - 1][y].dir_y);
		//if(r > 0)
		{
			(&c[*arrows])->x = x - 1;
			(&c[*arrows])->y = y;
			*arrows += 1;
		}
		//else
		//	printf("obstaculo\n");
	}
	if ((ft_try(data, 0, 1, x, y - 1)))
	{
		//printf("  set %d %d\n", x - 1, y);
//		printf("  set  %d %d with %d %d\n", x, y - 1, (*a_map)[x][y - 1].dir_x, (*a_map)[x][y - 1].dir_y);
		//if (r > 0)
		{
			(&c[*arrows])->x = x;
			(&c[*arrows])->y = y - 1;
			*arrows += 1;
		}
		//else
		//	printf("obstaculo\n");
	}
	if ((ft_try(data, -1, 0, x + 1, y)))
	{
		//printf("  set %d %d\n", x, y - 1);
//		printf("  set  %d %d with %d %d\n", x + 1, y, (*a_map)[x + 1][y].dir_x, (*a_map)[x + 1][y].dir_y);
		//if (r > 0)
		{
			(&c[*arrows])->x = x + 1;
			(&c[*arrows])->y = y;
			*arrows += 1;
		}
		//else
		//	printf("obstaculo\n");
	}
	if  ((ft_try(data, 0, -1, x, y + 1)))
	{
		//printf(" set %d %d\n", x + 1, y);
	//	printf("  set  %d %d with %d %d\n", x, y + 1, (*a_map)[y + 1][x].dir_x, (*a_map)[y + 1][x].dir_y);
//		printf("  set  %d %d with %d %d\n", x, y + 1, (*a_map)[x][y + 1].dir_x, (*a_map)[x][y + 1].dir_y);
		//if (r > 0)
		{
			(&c[*arrows])->x = x;
			(&c[*arrows])->y = y + 1;
			*arrows += 1;
		}
		//else
		//	printf("obstaculo\n");
	}
}

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
		{
			//printf("i: %d j: %d\n", i, j);
			(&a_map[i][j])->used = 0;
		}
	}
}

void	ft_fix_border(t_data *data)
{
	int i;
	int j;

	i = -1;
	while (++i < data->map_width)
	{
		(&data->arrow_map[0][i])->dir_x = 1;
		(&data->arrow_map[0][i])->dir_y = 0;
		(&data->arrow_map[data->map_height - 1][i])->dir_x = -1;
		(&data->arrow_map[data->map_height - 1][i])->dir_y = 0;

	}
}

void	ft_update_arrow_map(t_data *data)
{
	int				i;
	int				arrows;
	t_arrow			**a_map;
	t_coordinate	history[data->map_height * data->map_width];
	
	a_map = data->arrow_map;
	//printf("height %d width %d total %d\n", data->map_height, data->map_width, data->map_height *data->map_width);
	//exit (0);
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
		//printf("%d\n",data->arrow_map[8][16].dir_x);
		i++;
	}
	//exit(0);
	ft_fix_border(data);
	//printf("arrow_map fin\n");
	//exit(0);
}

void	ft_update_extra_maps(t_data *data)
{
	t_sprite	*s;
	int			**c_map;
	int			y;
	int			x;

//	printf("----------update map----------\n");
	c_map = data->collision_map;
//	printf("c_map %p\n", c_map);
	y = -1;
	while (++y < data->map_height)
	{
	//	printf("fila %d\n", y);
		x = -1;
		while (++x < data->map_width)
		{
	//		printf("  columna %d\n", x);
			c_map[y][x] = data->map[y][x];
		}
	}
//	printf("sale del while\n");
	y = -1;
	s = data->sprite_buffer;
//		printf("va a empezar while \n");
	while (++y < data->sprites_num)
	{
//		printf("intenta sprite -%d-, (%d, %d) texture %d \n", s[y].comprobador, (int)(s[y].y), (int)(s[y].x), s[y].texture);
//		s[y].y = s[y].back_y;
//		s[y].x = s[y].back_x;
//	printf("muere? ");
		c_map[(int)s[y].x][(int)s[y].y] = 1;//he cambiadp x por y, fallaba cuaando x era 42 h puede ser > max w
//	printf(" no\n");
	}
//	printf("update arrow start\n");
	ft_update_arrow_map(data);
//	printf("update arrow nd\n");
}

int		ft_loop_hook(void *params)
{
//	printf("???\n");
	t_data	*data;
	t_mlx	*mlx;
	int		moved;
	static int frame;

	//printf("loophook_start\n");
	data = (t_data *)params;
	t_player	*player = data->player; 
	mlx = data->mlx;
//	printf("1\n");
	moved = ft_move(data, data->player);
//	printf("2\n");
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
//	printf("3\n");
//		printf("start_render\n");
/////		ft_move_soldiers(data);
		ft_render(data, data->mlx, data->player, data->map);
//	printf("4\n");
		ft_lifebar(data);
//	printf("5\n");
		mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->screen, 0, 0);
//	printf("5.1\n");
		data->animation_num++;
//	printf("5.2\n");
		ft_update_extra_maps(data);
//	printf("6\n");
		ft_move_soldiers(data);            //<-- move soldiers
//	printf("7\n");
		if (data->animation_num >= data->animation_cycle)
			data->animation_num = 0;
//		printf("llega\n");
		//getchar();
//		printf("render_completed\n");
	}
	frame++;
	//printf("fin loop_hook\n");
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
//	free(t);
	//printf("sin problemas\n");
}

void	ft_free_textures(t_data *data)
{
	int i;
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
	free(data->mlx->n_img);
	free(data->mlx->s_img);
	free(data->mlx->e_img);
	free(data->mlx->w_img);
	free(data->mlx->skybox);
	i = -1;
	while (++i < data->sprite_tex_num)
		ft_free_texture(data, &data->sprite_tex_buffer[i]);
	free(data->sprite_tex_buffer);
}

void	ft_free_sprites(t_data *data)
{
	t_sprite	*s;
	
	s = data->sprite_buffer;
	free(s);
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

void	ft_lifebar(t_data *data)
{
	t_player	*p;
	int			mod_y;
	int			mod_x;
	int			start_x;
	int			start_y;
	int			end_x;
	int			end_y;
	int			health_ptg;
	int			*img;

	p = data->player;
	img = (int*)data->mlx->screen_data;
	start_y = data->res_y / 15;
	start_x = data->res_x / 15;
	end_x = start_x + data->res_x / 3;
	end_y = start_y + data->res_y / 15;
	health_ptg = (end_x - start_x) * p->health / 100 + start_x;
	mod_y = start_y;
	while (mod_y <= end_y)
	{
		//printf("moved  \n");
		mod_x = start_x;
		while (mod_x <= end_x)
		{
			if (mod_y == start_y || mod_y == end_y ||
					mod_x == start_x || mod_x == end_x)
				img[mod_y * data->res_x + mod_x] = 8355840;
			else if (mod_x <= health_ptg)
				img[mod_y * data->res_x + mod_x] = 16711680;
			mod_x++;
		}
		mod_y++;
	}
}

void	ft_update_hud(t_data *data)
{
	int			screen_x;
	int			screen_y;
	double		x;
	double		y;
	double		x_step;
	double		y_step;
	t_texture	*t;
	int			*img;
	int			*screen;
	int			color;

	t = data->hud;
	img = t->addr;
	//printf("img %p\n", img);
	screen_y = data->res_y - (int)data->res_y / 7;
	y = 0;
	//printf("screen_y %d\n", screen_y);
	//exit(0);
	screen = (int*)data->mlx->screen_data;
	x_step = (double)t->width / (double)data->res_x;
	y_step = (double)t->height / ((double)data->res_y - screen_y);
	//printf("1(while - 1)\n");
	//printf("y_step %f\n", y_step);
	//exit(0);
	while (screen_y < data->res_y)
	{		
	//	printf("1(while)\n");
		screen_x = 0;
		x = 0;
		while (screen_x < data->res_x)
		{
	//		printf("screen_x: %d, screem_y: %d\n", screen_x, screen_y);
	//		printf("tex_x: %f, tex_y: %f\n", x, y);
	//		printf("1(while + 1)\n");
	//		printf("res_x %d, res_y %d\n", data->res_x, data->res_y);
	//		printf("t_width %d\nt_height %d\naccede en %d\n", t->width, t->height, (int)y * t->width + (int)x);
	//		printf("step_x %f, step_y %f\n", x_step, y_step);
			color = img[(int)y * (int)t->width + (int)x];
	//		printf("aqui llega\n");
			if (color != 9961608)
			{
				//printf("entra\n");
			//	printf("screen_y %d, screen_x %d\n", screen_y, screen_x);
				screen[screen_x + data->res_x * screen_y] = color;
			//	printf("llega\n");
			}

			x += x_step;
			screen_x++;
			if (x >= t->width)
				x = t->width - 1;
		}
		//exit(0);
		y += y_step;
		screen_y++;
		if (y >= t->height)
			y = t->height - 1;
	}
	//exit(0);
}

int		ft_is_soldier(t_data *data, int x, int y)
{
	int i;
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
	return  (0);
}

void	ft_print_arrow(t_data *data, int x_a, int y_a)
{
	t_arrow **a_map;
	int		**c_map;
	
	a_map = data->arrow_map;
	c_map = data->collision_map;
	//printf("print arrow y: %d x: %d\n", y_a, x_a);
	int x = a_map[y_a][x_a].dir_x;
	int y = a_map[y_a][x_a].dir_y;

	//printf("(x %d y %d)", x, y);
	if (ft_is_soldier(data, y_a, x_a))
		printf("x");
	else if (c_map[y_a][x_a])
		printf("o");
	else if (x)
	{
		if (x > 0)
			printf("v");
		else
			printf("^");
	}
	else
	{
		if (y < 0)
			printf("<");
		else
			printf(">");
	}
	//printf("(%2d,%2d)", a_map[y_a][x_a].dir_x, a_map[y_a][x_a].dir_y);
}

int		ft_key_hook(int keycode, void *params)
{
//	printf("pressed keycode: %d\n", keycode);
	t_data *data;

	data = (t_data*)params;
	//printf("code: %d\n", keycode);
//	if (keycode == 53)
//	{
		/*data->player->move_them++;
		if (data->player->move_them > 8)
			data->player->move_them = 1;
		printf("value: %d\n", data->player->move_them);*/
		int y = -1;
		printf("\n");
		while (++y < data->map_height)
		{
			int x = -1;
			while (++x < data->map_width)
			{
				//printf("print arrow (%d, %d)\n", x, y);
				ft_print_arrow(data, x, y);
			}
			printf("\n");
		}
	//	exit(0);
//	}
	if (keycode == 53)
	{
		ft_free_map(data);
	//	mlx_destroy_image(data->mlx->ptr, data->img);
	//	free(data->img);
	//	printf("  free %p\n", data->buffer_z);
		free(data->buffer_z);
		ft_free_textures(data);
		free(data->sprite_buffer);
		//	ft_free_sprites(data);
	//	printf("  free %p\n", data->player);
		free(data->player);
		ft_free_mlx(data->mlx);
////////getchar();
		exit(0);
	}
	ft_check_movement(data, keycode, 1);
//	ft_move_soldiers(data);
	return (0);
}
