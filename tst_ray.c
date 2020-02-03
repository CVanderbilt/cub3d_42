/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_ray.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:08:58 by eherrero          #+#    #+#             */
/*   Updated: 2020/02/03 21:11:45 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_step_calc(t_ray *ray, t_player *player)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->x - ray->x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->x + 1.0 - player->x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->y - ray->y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->y + 1.0 - player->y) * ray->delta_dist_y;
	}
}

void		ft_init_ray(t_ray *ray, t_player *player, double camera_x)
{
	ray->dir_x = player->dir_x + player->plane_x * camera_x;
	ray->dir_y = player->dir_y + player->plane_y * camera_x;
	ray->x = (int)(player->x);
	ray->y = (int)(player->y);
	ray->hit = 0;
	ray->side = 0;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ft_step_calc(ray, player);
}

t_texture	*ft_switch_texture(t_data *data, t_ray *ray)
{
	int item;

	if (ray->side == 0)
		item = ray->dir_x > 0 ? 1 : 2;
	else
		item = ray->dir_y > 0 ? 3 : 4;
	if (item == 1)
		return (data->mlx->n_img);//n
	if (item == 2)
		return (data->mlx->s_img);//s
	if (item == 3)
		return (data->mlx->e_img);//e
	return (data->mlx->w_img);//w
}

int			ft_tex_xcalc(t_ray *ray, t_texture *tex, double wall_x)
{
	int ret;

	ret = (int)(((wall_x - floor(wall_x)) * (double)(tex->width)));
	if (!ray->side && ray->dir_x > 0)
		ret = tex->width - ret - 1;
	if (ray->side && ray->dir_y < 0)
		ret = tex->width - ret - 1;
	return (ret);
}

void		ft_paint_sky_col(t_ray *ray, t_data *data, t_paint_col *ft, int *img)
{
	t_texture	*t;
	float		a;
	int			i;
	int			j;
	int			offset;
	float		step;
	int			*sky_img;

	t = data->mlx->skybox;
	sky_img = t->addr;
	//printf("1\n");
	//printf("ray_y %f, ray_x %f\n", ray->dir_y, ray->dir_x);
	a = atan2(ray->dir_y, ray->dir_x) * 180 / M_PI + 90;
	a += a > 0 ? 0 : 360;
	//a = a > 1.57 ? 1.57 : a;
	i = 0;
	//printf("a = %f\n", a);
	//printf("h = %d\n", t->height);
	//printf("w = %d\n", t->width);

	float kk = a * t->height / 360;
	if (kk >= t->height)
		kk = t->height - 1;
	//printf("pintamos la fila %f en la columna %d\n", kk, ray->col);
	offset = t->width * (int)kk;;
	//printf("-kk-offset %d\n", offset);
	//printf("a -> %f\n", a);
	//printf("empieza a pintar\n");
	//int mod = data->res_y / t->width;	
	//printf("2\n");
	while (i < ft->draw_s)
	{
		//printf("-%d-\n", i);
		//printf("ray_col %d\n", ray->col);
		//printf("offset %d\n", offset);
		j = i * t->width / data->res_y;
		//printf("j %d\n", j);
		//printf("pinta pixel en ray->col %d + i %d * data->res_y %d = %d\n", ray->col, i, data->res_y, ray->col + i * data->res_y);
		//printf("-pp-%d color %d\n", offset + j, sky_img[offset + j]);
		//printf("    pinta en %d la posicion %d\n", i, offset + j);
	//	printf("-----%d\n", ray->col + i * data->res_y);
	//	printf("  ray_col %d\n  i %d\n  draw_s %d\n", ray->col, i, ft->draw_s);
	//	printf("j %d, offset %d\n", j, offset);
		img[ray->col + i * data->res_y] = sky_img[offset + j];
		i++;
	}
	//printf("3\n");
	//printf("-kk-ultimo pintado %d\n", offset + j);
	//exit(0);
}	

void		ft_paint_col(t_ray *ray, t_data *data)
{
	t_texture	*tex;
	t_paint_col	ft;
	int			*img;

	//printf("  paint_col start\n");


	img = (int *)data->mlx->screen_data;
	ft.line_height = (int)(data->mlx->y / ray->perp_wall_dist);
	tex = ft_switch_texture(data, ray);
	ft.draw_s = -ft.line_height / 2 + data->mlx->y / 2;
	ft.draw_s = ft.draw_s < 0 ? 0 : ft.draw_s;
	ft.draw_end = (ft.line_height) / 2 + data->mlx->y / 2;
	if (ft.draw_end >= data->mlx->y)
		ft.draw_end = data->mlx->y - 1;
	ft.wall_x = ray->side ? data->player->x + ray->perp_wall_dist * ray->dir_x :
		data->player->y + ray->perp_wall_dist * ray->dir_y;
	ft.tex_x = ft_tex_xcalc(ray, tex, ft.wall_x);
	ft.step = 1.0 * tex->height / (ft.line_height/* + data->player->h*/);
	ft.tex_pos = (ft.draw_s - data->mlx->y / 2 + ft.line_height / 2) * ft.step;
	ft_paint_sky_col(ray, data, &ft, img);
	ft.mul = (tex->height) * ft.tex_x;


	//printf("  pinta desde %d hasta %d\n", ft.draw_s, ft.draw_end);
	while (ft.draw_s++ < ft.draw_end)
	{
		ft.tex_y = (int)ft.tex_pos & ((int)tex->height - 1);
		ft.tex_pos += ft.step;
		ft.color = tex->addr[ft.mul + ft.tex_y];
		//if (ray->col + (ft.draw_s - 1) * data->res_y >= data->res_y * data->res_x)
			img[ray->col + (ft.draw_s - 1) * data->res_y] = ft.color;
	}
	//printf("  paint_col antes while 2\n");
	while (ft.draw_end < data->mlx->y)
	{
		//printf("---%d\n", ray->col + ft.draw_end * data->res_y);
		img[ray->col + (ft.draw_end - 1) * data->res_y] = 6579300;
		ft.draw_end++;
	}
	//getchar();
}

double		ft_ray_dist(t_ray *ray, t_player *player)
{
	if (ray->side)
		return ((ray->y - player->y + (1 - ray->step_y) / 2) / ray->dir_y);
	return ((ray->x - player->x + (1 - ray->step_x) / 2) / ray->dir_x);
}

void		ft_ray_side_dist(t_ray *ray)
{
	if (ray->side_dist_x < ray->side_dist_y)
	{
		ray->side_dist_x += ray->delta_dist_x;
		ray->x += ray->step_x;
		ray->side = 0;
	}
	else
	{
		ray->side_dist_y += ray->delta_dist_y;
		ray->y += ray->step_y;
		ray->side = 1;
	}
}

int			ft_get_gridx(double a, int sections)
{
	double	sector;

	sector = 360 / sections;
	a += sector / 2;
	//printf("  a_mod: %f\n", a);
	if ((int)(a * 10) >= 0)
	{
	//	printf("  positivo\n");
		return ((int)(a / sector));
	}
	a *= -1;
	//printf("  negativo\n");
	return (7 - (int)(a / sector));	
}

int			ft_get_gridy(t_data *data, t_sprite *s, int states)
{
	int n;

	//return (0);
	if (!s->moved)
		return (0);
	n = data->animation_cycle / (states - 1);
	//printf("\n\nret %d\n", data->animation_num / n + 1);
	//printf("n %d\n", n);
	//printf("animation_num %d\n", data->animation_num);
	//if (data->animation_num / n + 1 > 4)
	//	getchar();
	return (data->animation_num / n + 1);
}
t_texture	*ft_get_sprite_texture(t_data *data, t_sprite *s)
{
	t_player	*p;
	t_texture	*t;
	double		a;
	double		sector;
	int		x_grid;
	int			y_grid;

	//a = atan2(ray->dir_y, ray->dir_x) * 180 / M_PI + 90;
	p = data->player;
	t = &data->sprite_tex_buffer[s->texture];
	t->offset = 0;
	//printf("tex: %d -- tex_num: %d\n", sprite->texture, data->sprite_tex_num);
	if (s->texture >= data->sprite_tex_num)
		ft_cub_error();
	if (s->type == 0)
		return (t);
	//double angle = atan2(p2y, p2x) - atan2(p1y, p1x);
	//6,28319 en radianes 360
	sector = 360 / t->a_directions;
	a = ((atan2(s->dir_y, s->dir_y) * 180 / M_PI + 90) - (atan2(p->dir_y, p->dir_x) * 180 / M_PI + 90));
	//a *= a > 0 ? 1 : -2;
	//printf("a: %f\na_mod %f\n", a, a + 45/2);
	//x_grid = a / sector;
	//a = 0;
	//printf("x_grid %f\n", x_grid);
	//x_grid = x_grid > t->a_directions ? t->a_directions : x_grid;
	//x_grid = x_grid * 10 >= 0 ? x_grid : (int)x_grid + t->a_directions - 1;

	y_grid = ft_get_gridy(data, s, t->a_states);
	//printf("grid_y %d\n", y_grid);
	x_grid = ft_get_gridx(a, t->a_directions);
	//printf("diff: %f, a_state: %f\n", a, x_grid);


	printf("width %f height %f realw %d realh %d\n", t->width, t->height, t->real_width, t->real_height);
	//getchar();

	printf("y_grid: %d adds %f\n", y_grid, y_grid * (t->real_width) * t->height);
	printf("x_grid %d adds %f\n", x_grid, (int)x_grid * t->width);
	t->offset = (int)(x_grid * t->width) + (int)(y_grid * t->real_width * t->height);
	return (t);
}

void		ft_paint_one_sprite(t_data *data, t_sprite *sprite)
{
	t_player	*p;
	double		inv_det;
	double		sprite_x;
	double		sprite_y;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;

	int			sprite_h;
	int			sprite_w;

	int			draw_start_y;
	int			draw_end_y;

	int			draw_start_x;
	int			draw_end_x;
	
	int			stripe;

	int			tex_x;
	int			tex_y;

	t_texture	*t;
	int			*img;
	int			*screen;
	int			y;

//	printf("  pinta una\n");
	screen =(int*)data->mlx->screen_data;

//	printf("intenta sacar textura\n");
	t = ft_get_sprite_texture(data, sprite);
	//printf("la saca\n");
	img = t->addr;

	p = data->player;
	sprite_x = sprite->x - p->x;
	sprite_y = sprite->y - p->y;
	inv_det = 1.0 / (p->plane_x * p->dir_y - p->plane_y * p->dir_x);
	
	transform_x = inv_det * (p->dir_y * sprite_x - p->dir_x * sprite_y);
	transform_y = inv_det * (-p->plane_y * sprite_x + p->plane_x * sprite_y);

//	printf("transform_x %f\n", transform_x);
//	printf("transform_y %f\n", transform_y);

	sprite_screen_x = (int)((data->res_x / 2) * (1 + transform_x / transform_y));
	
	sprite_h = abs((int)(data->res_y / transform_y));

	draw_start_y = -(sprite_h/* + p->h*/) / 2 + data->res_y / 2;
	//draw_start_y += p->h;
	if (draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = sprite_h / 2 + data->res_y / 2;
	if (draw_end_y >= data->res_y)
		draw_end_y = data->res_y - 1;
	
	sprite_w = abs((int)(data->res_y / transform_y));

	draw_start_x = -sprite_w / 2 + sprite_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = sprite_w / 2 + sprite_screen_x;
	if (draw_end_x >= data->res_x)
		draw_end_x = data->res_x - 1;
	stripe = draw_start_x;
	if (tex_x >= t->width)
		tex_x = t->width - 1;
	if (tex_x < 0)
		tex_x = 0;
//	printf("va a entrar a bucle\n");
//	printf("pinta desde x(%d a %d) y desde y(%d a %d)\n", draw_start_x, draw_end_x ,draw_start_y, draw_end_y);
	while (stripe < draw_end_x)
	{
	//	printf("stripe: %d\n", stripe);
		tex_x = (int)(256 * (stripe - (-sprite_w / 2 + sprite_screen_x)) * t->width / sprite_w) / 256;
		y = draw_start_y;
	//	printf("tex_x %d\n", tex_x);
	//printf("pinta desde x(%d a %d) y desde y(%d a %d)\n", draw_start_x, draw_end_x ,draw_start_y, draw_end_y);
		if (transform_y > 0 && stripe > 0 && stripe < data->res_x && transform_y < data->buffer_z[stripe])
			while (y < draw_end_y)
			{
				/*float step = draw_end_y / draw_start_y;

				int tex_y = step * y;
				int	color = img[t->width * tex_y + tex_x];
				if (color != 9961608)
					screen[y * data->res_y + data->res_x - stripe] = color;
*/
				
				int d = (y) * 256 - data->res_y * 128 + sprite_h * 128;
				int	tex_y = ((d * t->height) / sprite_h) / 256;
		//		printf("  draw_end %d\n", draw_end_y);
				//printf("t_height %d\n", t->height);
	//printf("sprite_h %d\n", sprite_h);
		//printf("  tex_y %d\n", tex_y);

				//printf("selecciona color pos %d\n", t->width * tex_y + tex_x);
				//printf(" sprite_h %d\n", sprite_h);
			//	printf(" d %d\n", d);
				//printf(" t->width %d\n", t->width);
			//	printf(" tex_y %d\n", tex_y);
			//	printf(" tex_x %d\n", tex_x);
				if (tex_y >= t->height)
					tex_y = t->height - 1;
				if (tex_y < 0)
					tex_y = 0;
				//t->offset += t->real_width * tex_y + tex_x;
			//	if (t->offset >= t->real_width * t->real_height)
			//		t->offset = t->real_width * t->real_height - 1;
				int color = img[t->offset + t->real_width * tex_y + tex_x];
			//	int	color = img[t->offset];
				if (color != 9961608)
					screen[y * data->res_y + data->res_x - stripe] = color;
				y++;
			}
		stripe++;
	}
	//printf("  acaba una\n");

}




/*

void		ft_paint_one_sprite(t_data *data, t_sprite *sprite)
{
	t_player	*p;
	double		inv_det;
	double		sprite_x;
	double		sprite_y;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;

	int			sprite_h;
	int			sprite_w;

	int			draw_start_y;
	int			draw_end_y;

	int			draw_start_x;
	int			draw_end_x;
	
	int			stripe;

	int			tex_x;
	int			tex_y;

	t_texture	*t;
	int			*img;
	int			*screen;
	int			y;

	printf("  pinta una\n");
	screen =(int*)data->mlx->screen_data;

	t = sprite->texture;
	img = t->addr;

	p = data->player;
	sprite_x = sprite->x - p->x;
	sprite_y = sprite->y - p->y;
	inv_det = 1.0 / (p->plane_x * p->dir_y - p->plane_y * p->dir_x);
	
	transform_x = inv_det * (p->dir_y * sprite_x - p->dir_x * sprite_y);
	transform_y = inv_det * (-p->plane_y * sprite_x + p->plane_x * sprite_y);

	printf("transform_x %f\n", transform_x);
	printf("transform_y %f\n", transform_y);

	sprite_screen_x = (int)((data->res_x / 2) * (1 + transform_x / transform_y));
	
	sprite_h = abs((int)(data->res_y / transform_y));

	draw_start_y = -sprite_h / 2 + data->res_y / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = sprite_h / 2 + data->res_y / 2;
	if (draw_end_y >= data->res_y)
		draw_end_y = data->res_y - 1;
	
	sprite_w = abs((int)(data->res_y / transform_y));

	draw_start_x = -sprite_w / 2 + sprite_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = sprite_w / 2 + sprite_screen_x;
	if (draw_end_x >= data->res_x)
		draw_end_x = data->res_x - 1;
	stripe = draw_start_x;
	printf("va a entrar a bucle\n");
	printf("pinta desde x(%d a %d) y desde y(%d a %d)\n", draw_start_x, draw_end_x ,draw_start_y, draw_end_y);
	while (stripe < draw_end_x)
	{
		printf("stripe: %d\n", stripe);
		tex_x = (int)(256 * (stripe - (-sprite_w / 2 + sprite_screen_x)) * t->width / sprite_w) / 256;
		y = 0;
		printf("tex_x %d\n", tex_x);
		if (transform_y > 0 && stripe > 0 && stripe < data->res_x && transform_y < data->buffer_z[stripe])
			while (y < draw_end_y)
			{
				int d = (y) * 256 - data->res_y * 128 + sprite_h * 128;
				int	tex_y = ((d * t->height) / sprite_h) / 256;
				//printf("t_height %d\n", t->height);
	printf("sprite_h %d\n", sprite_h);
		printf("  tex_y %d\n", tex_y);

				//printf("selecciona color pos %d\n", t->width * tex_y + tex_x);
				//printf(" sprite_h %d\n", sprite_h);
				//printf(" d %d\n", d);
				//printf(" t->width %d\n", t->width);
				//printf(" tex_y %d\n", tex_y);
				//printf(" tex_x %d\n", tex_x);
				int color = img[t->width * tex_y + tex_x];
				if (color != 9961608)
					screen[y * data->res_y + data->res_x - stripe] = color;
				y++;
			}
		stripe++;
	}
	printf("  acaba una\n");

}



*/



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
	
	//printf("empieza a pintar sprites\n");
	p = data->player;
	sprite = data->sprite_buffer;
	i = -1;
    while (++i < data->sprites_num)
	{
		orden[i] = i;
		distancias[i] = ((p->x - sprite[i].x) * (p->x - sprite[i].x) + (p->y - sprite[i].y) * (p->y - sprite[i].y));
    }
	ft_sort_sprites(orden, distancias, data->sprites_num);
	i = 0;
	while (i < data->sprites_num)
	{
		ft_paint_one_sprite(data, sprite + orden[i]);
		i++;
	}
	//printf("acaba de pintar sprites\n");
}

int			ft_render(t_data *data, t_mlx *mlx, t_player *player, int **map)
{
	t_ray	ray;
	double	camera_x;
	int		step;
	int		ray_col;

	//printf("ft_render start\n");
	ray_col = 0;
	//ft_paint_floor(data);
	while (ray_col < data->res_x)
	{
		//printf("--kk--%d\n", ray_col);
		camera_x = 2 * ray_col / (double)(mlx->x) - 1;
		ft_init_ray(&ray, player, camera_x);
		ft_step_calc(&ray, player);
		while (ray.hit == 0)
		{
			ft_ray_side_dist(&ray);
			if (map[ray.x][ray.y] > 0)
				ray.hit = 1;
		}
		ray.perp_wall_dist = ft_ray_dist(&ray, player);
		//printf("buffer_z %p\n", data->buffer_z);
		//printf("mete en el buffer dist %f en posicion %d\n", ray.perp_wall_dist, ray_col);
		data->buffer_z[ray_col] = ray.perp_wall_dist;
		//printf("1\n");
		ray.col = mlx->x -  ray_col;
		//printf("2\n");
		ft_paint_col(&ray, data);
		//printf("3\n");
		ray_col += 1;
	}
	//printf("paint sprites\n");
	ft_paint_sprites(data);
	ft_update_hud(data);
	//mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->screen, 0, 0);
	return (1);
}
