#include "cub3d.h"

void	ft_step_calc(t_ray *ray, t_player *player)
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

void	ft_print_ray(t_ray *ray)
{
	printf("\nray\n");
	printf("dir_x %f\ndir_y%f\n", ray->dir_x,  ray->dir_y);
	printf("delta_dist_x %f\ndelta_dist_y %f\n", ray->delta_dist_x, ray->delta_dist_y);
	printf("step_x %d\nstep_y %d\n", ray->step_x, ray->step_y);
}

void	ft_init_ray(t_ray *ray, t_player *player, double camera_x)
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
//	if (player->kk)
//		ft_print_ray(ray);
}

int		ft_color_switch(t_ray *ray)
{
	int item;

	if  (ray->side == 0)
		item = ray->dir_x > 0 ? 1 : 2;
	else
		item = ray->dir_y > 0 ? 3 : 4;
	if (item == 1)//west
		return (16711680);//rojo
	if (item == 2)//east
		return (65280);//verde
	if (item == 3)//south
		return (255);//azul
	if (item == 4)//north
		return (16777215);//blanco
	return (16776960);//??
}

t_texture	*ft_switch_texture(t_data *data, t_ray *ray)
{
	int item;

	//return (data->mlx->n_img);
	if (ray->side == 0)
		item = ray->dir_x > 0 ? 1 : 2;
	else
		item = ray->dir_y > 0 ? 3 : 4;
	//1-w 2-e 3-s 4-n
	if (item == 1)
		return (data->mlx->w_img);
	if (item == 2)
		return (data->mlx->e_img);
	if (item == 3)
		return (data->mlx->s_img);
	return (data->mlx->n_img);
}

void	ft_paint_col(t_ray *ray, t_data *data)
{
	t_mlx		*mlx = data->mlx;
	t_player	*player = data->player;
	t_texture	*tex;
	t_paint_col	ft;

	ft.line_height = (int)(mlx->y / ray->perp_wall_dist);
	tex = ft_switch_texture(data, ray);
	//tex = data->mlx->n_img;
	//printf("textura: %p\naddr: %p\n", tex->img, tex->addr);
	ft.draw_start = -ft.line_height / 2 + mlx->y / 2;
	if(ft.draw_start < 0)
		ft.draw_start = 0;
	ft.draw_end = ft.line_height / 2 + mlx->y / 2;
	if(ft.draw_end >= mlx->y)
		ft.draw_end = mlx->y - 1;
	if(ray->side == 0)
		ft.wall_x = player->y + ray->perp_wall_dist * ray->dir_y;
	else
		ft.wall_x = player->x + ray->perp_wall_dist * ray->dir_x;
	ft.wall_x -= floor((ft.wall_x));
	ft.tex_x = (int)(ft.wall_x * (double)(tex->width));
	if(ray->side == 0 && ray->dir_x > 0)
		ft.tex_x = tex->width - ft.tex_x - 1;
	if(ray->side == 1 && ray->dir_y < 0)
		ft.tex_x = tex->width - ft.tex_x - 1;
	ft.step = 1.0 * tex->height / ft.line_height;
	ft.tex_pos = (ft.draw_start - mlx->y / 2 + ft.line_height / 2) * ft.step;
	for(int y = ft.draw_start; y < ft.draw_end; y++)
	{
		ft.tex_y = (int)ft.tex_pos & (tex->height - 1);
		ft.tex_pos += ft.step;
		//printf("busca en %p\n height %d * tex_y %d + tex_x %d\n", tex->addr, tex->height, ft.tex_y, ft.tex_x);
		//exit(0);
		ft.color = tex->addr[tex->height * ft.tex_y + ft.tex_x];
		mlx_pixel_put(mlx->ptr, mlx->window, ray->col, y, ft.color);
	}
}

double	ft_ray_dist(t_ray *ray, t_player *player)
{
	if (ray->side)
		return ((ray->y - player->y + (1 - ray->step_y) / 2) / ray->dir_y);
	return ((ray->x - player->x + (1 - ray->step_x) / 2) / ray->dir_x);
}

void	ft_ray_side_dist(t_ray *ray)
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

int		ft_render(t_data *data, t_mlx *mlx, t_player *player, int **map)
{
	t_ray	ray;
	double	camera_x;
	int		step;
	int		ray_col;

	//mlx->img = mlx_new_image(mlx->ptr, mlx->x, mlx->y);
/*
	if (player->dir_x >= 0)
	{
		printf("invertido\n");
		ray.col = mlx->x;
		ray_col_step = -1;
		ray_col_last = 0;
	}
	else
	{
		ray.col = 0;
		ray_col_step = 1;
		ray_col_last = mlx->x;
	}*/
	ray_col = 0;
	while (ray_col < mlx->x)
	{
		camera_x = 2 * ray_col / (double)(mlx->x) - 1;
		//printf("camera_x: %f\n", camera_x);
		ft_init_ray(&ray, player, camera_x);
	//	if (player->dir_x >= 0)
	//	{
	//		camera_x *= -1;
	//	}
		ft_step_calc(&ray, player);
		while (ray.hit == 0)
		{
			ft_ray_side_dist(&ray);
			if (map[ray.x][ray.y] > 0)
				ray.hit = 1;
		}
		ray.perp_wall_dist = ft_ray_dist(&ray, player);
		ray.col = mlx->x - ray_col;
		ft_paint_col(&ray, data);
		ray_col += 1;
	}
	return (1);
}
/*
int		ft_init_mlx(t_mlx *mlx, int x, int y, char *title)
{
	mlx->x = x;
	mlx->y = y;
	mlx->title = title;
	mlx->ptr = mlx_init();
	if (!mlx->ptr)
		return (0);
	if (x > 0 && y > 0)
		if (!(mlx->window = mlx_new_window(mlx->ptr, x, y, title)))
			return (0);
	return (1);
}*/
/*
int		main(void)
{
	t_mlx		mlx;
	t_player	player;

	player.x = 11;
	player.y = 11;
	player.dir_x = 1;
	player.dir_y = 0;
	player.plane_x = 0;
	player.plane_y = 0.66;
	player.h = 0;
	if (!ft_init(&mlx, 500, 500, "tst"))
		return (1);
	ft_render(&mlx, &player, g_map);
	mlx_loop(mlx.ptr);
	return (0);
}
*/
