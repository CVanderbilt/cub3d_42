/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:43:11 by eherrero          #+#    #+#             */
/*   Updated: 2020/01/27 11:37:03 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*void	ft_data_set(t_data *data)
{
	
}*/

void	ft_init_player(t_player *player, double r_speed, double m_speed)
{
	printf("init_player\n");
	printf("r_speed: %f\nm_speed: %f\n", r_speed, m_speed);
	player->x = 0;
	player->y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->h = 0;
	player->rot_speed = r_speed;
	player->mov_speed = m_speed;
}

void	ft_init_texture(t_mlx *mlx, t_texture *tex, char *path)
{
	char	*line;
	int		fd;
	int		endian;

	endian = 1;
	fd = open(path, O_RDONLY);
	get_next_line(fd, &line);
	get_next_line(fd, &line);
	get_next_line(fd, &line);
	get_next_line(fd, &line);
	close(fd);
	fd = 0;
	while (!ft_isdigit(line[fd]))
		fd++;
	tex->width = ft_atoi(line + fd);
	while (ft_isdigit(line[fd]))
		fd++;
	while (!ft_isdigit(line[fd]))
		fd++;
	tex->height = ft_atoi(line + fd);
	tex->bpp = 4;
	tex->size_line = tex->bpp * tex->width;
	//mlx_xpm_file_to_image ( void *mlx_ptr, char *filename, int *width, int *height );
	tex->img = mlx_xpm_file_to_image(mlx->ptr, path, &(tex->width), &(tex->height));
	//mlx_get_data_addr ( void *img_ptr, int *bits_per_pixel, int *size_line, int *endian );
	tex->addr = (int *)mlx_get_data_addr(tex->img, &(tex->bpp), &(tex->size_line), &endian);
	//printf("inicializad textura: %p, cargada en %p\n", tex->img, tex->addr);
}

void	ft_init_mlx(t_data *data, char *map_name)
{
	t_mlx	*mlx;
	int		bpp;
	int		endian;
	int		size_line;

	endian = 1;
	bpp = 4;
	size_line = 500 * 4;
	mlx = data->mlx;
	printf("init_mlx: %p\n", mlx);
	//lx_new_image ( void *mlx_ptr, int width, int height
	//mlx->n_img = 0;
	mlx->x = data->res_x > 0 ? data->res_x : 500;
	mlx->y = data->res_y > 0 ? data->res_y : 500;
	//mlx->x = 500;
	//mlx->y = 500;
	mlx->ptr = mlx_init();
	mlx->screen = mlx_new_image(mlx->ptr, mlx->x, mlx->y);
	//mlx_get_data_addr ( void *img_ptr, int *bits_per_pixel, int *size_line, int *endian )
	mlx->screen_data = mlx_get_data_addr(mlx->screen, &bpp, &size_line, &endian);
	//mlx->n_img = mlx_new_image(mlx->ptr, 32, 32);
	//mlx_xpm_file_to_image ( void *mlx_ptr, char *filename, int *width, int *height );
	
	mlx->n_img = (t_texture*)malloc(sizeof(t_texture));
	mlx->s_img = (t_texture*)malloc(sizeof(t_texture));
	mlx->w_img = (t_texture*)malloc(sizeof(t_texture));
	mlx->e_img = (t_texture*)malloc(sizeof(t_texture));
	if (!mlx->n_img || !mlx->s_img || !mlx->e_img || !mlx->w_img)
		ft_memory_error();
	
	ft_init_texture(mlx, mlx->n_img, "brick.xpm");
	ft_init_texture(mlx, mlx->s_img, "stone.xpm");
	ft_init_texture(mlx, mlx->e_img, "metal.xpm");
	ft_init_texture(mlx, mlx->w_img, "wood.xpm");

	printf("n_img: %p\n", mlx->n_img);
	//mlx_put_image_to_window ( void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y )
	if (!mlx->ptr)
		ft_memory_error();	
	if (!(mlx->window = mlx_new_window(mlx->ptr, mlx->x, mlx->y, map_name)))
		ft_memory_error();
	//mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->n_img, 0, 0);
	printf("end_init_mlx\n");
}

void	ft_init_data(t_data *data, char *map_name, double r_speed, double m_speed)
{
	t_player	*player;
	t_mlx		*mlx;

	printf("init_data\n");
	//ft_data_set(data);
	player = (t_player *)malloc(sizeof(t_player));
	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!player || !mlx)
		ft_memory_error();
	data->player = player;
	data->mlx = mlx;
	ft_init_player(player, r_speed, m_speed);
	printf("get_map\n");
	ft_get_map(map_name, data);
	ft_init_mlx(data, map_name);
	
}

void	ft_loop(t_data *data)
{
	t_mlx *mlx;

	printf("1\n");
	mlx = data->mlx;
	printf("2\n");
	//mlx_loop_hook(mlx->ptr, ft_loop_hook, data);
	printf("3\n");
	//mlx_key_hook(mlx->window, ft_key_hook, data);
	mlx_hook(mlx->window, 2, 1, ft_key_hook, data);
	//mlx_int_param_KeyRelease(mlx->window, ft_key_release_hook, data);
	mlx_hook(mlx->window, 3, 0, ft_key_release_hook, data);
	mlx_loop_hook(mlx->ptr, ft_loop_hook, data);
	printf("loop\n");
	mlx_loop(mlx->ptr);
}

int main(int argc, char **argv)
{
	t_data		data;
	t_player	*p;

	ft_init_data(&data, "map.cub", 0.05, 0.1);
	//printf("alpha %f\n", (data.player)->alpha);
	(data.player)->kk = 0;
	p = data.player;
	printf("Rot_speed: %f\nMov_speed: %f\n", p->rot_speed, p->mov_speed);
	ft_loop(&data);

	return (0);
}
