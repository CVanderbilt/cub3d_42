/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:43:11 by eherrero          #+#    #+#             */
/*   Updated: 2020/01/29 19:14:07 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	player->moving_forward = 0;
	player->moving_backward = 0;
	player->moving_left = 0;
	player->moving_right = 0;
	player->rotating_right = 0;
	player->rotating_left = 0;
}

void	ft_init_texture(t_mlx *mlx, t_texture *t, char *path)
{
	char	*line;
	int		fd;
	int		e;

	e = 1;
	fd = open(path, O_RDONLY);
	get_next_line(fd, &line);
	printf("readed 0 >%s<\n", line);
	//free(line);
	get_next_line(fd, &line);
	printf("readed 1>%s<\n", line);
	//free(line);
	get_next_line(fd, &line);
	printf("readed 2>%s<\n", line);
	//free(line);
	get_next_line(fd, &line);
	//close(fd);
	fd = 0;
	printf("readed 3>%s<\n\n", line);
	while (!ft_isdigit(line[fd]))
		fd++;
	printf("width\nfd: %d\nline: %s\n", fd, line + fd);
	t->width = ft_atoi(line + fd);
	printf("???\n");
	while (ft_isdigit(line[fd]))
		fd++;
	while (!ft_isdigit(line[fd]))
		fd++;
	printf("height\n");
	t->height = ft_atoi(line + fd);
	t->bpp = 4;
	t->size_line = t->bpp * t->width;
	printf("image and addr\n");
	t->img = mlx_xpm_file_to_image(mlx->ptr, path, &(t->width), &(t->height));
	t->addr = (int *)mlx_get_data_addr(t->img, &(t->bpp), &(t->size_line), &e);
	printf("end\n");
}

void	ft_init_textures(t_data *data)
{
	t_mlx	*mlx;

	mlx = data->mlx;
	mlx->n_img = (t_texture*)malloc(sizeof(t_texture));
	mlx->s_img = (t_texture*)malloc(sizeof(t_texture));
	mlx->w_img = (t_texture*)malloc(sizeof(t_texture));
	mlx->e_img = (t_texture*)malloc(sizeof(t_texture));
	mlx->skybox = (t_texture*)malloc(sizeof(t_texture));
	mlx->sprite1 = (t_texture*)malloc(sizeof(t_texture));
	if (!mlx->n_img || !mlx->s_img || !mlx->e_img || !mlx->w_img)
		ft_memory_error();
	ft_init_texture(mlx, mlx->n_img, "brick.xpm");
	ft_init_texture(mlx, mlx->s_img, "stone.xpm");
	ft_init_texture(mlx, mlx->e_img, "metal.xpm");
	ft_init_texture(mlx, mlx->w_img, "wood.xpm");
	ft_init_texture(mlx, mlx->skybox, "skybox.xpm");
	ft_init_texture(mlx, mlx->sprite1, "sprite.xpm");
}
/*
void	ft_init_sprites(t_data *data)
{
	sprites_num = 1;
	sprites_id = (int*)malloc(sizeof(int) * sprites_num);
	sprites = (t_sprite*)malloc(sizeof(t_sprite) * sprites_num);
	sprites_id[0] = 0;
	sprites[0].id = 0;	
	sprites[0].texture = data->mlx->sprite1;	
}*/

void	ft_init_mlx(t_data *data, char *map_name)
{
	t_mlx	*mlx;
	int		bpp;
	int		e;
	int		size_line;

	e = 1;
	bpp = 4;
	size_line = 500 * 4;
	mlx = data->mlx;
	printf("init_mlx: %p\n", mlx);
	mlx->x = data->res_x > 0 ? data->res_x : 500;
	mlx->y = data->res_y > 0 ? data->res_y : 500;
	printf("ptr\n");
	mlx->ptr = mlx_init();
	mlx->screen = mlx_new_image(mlx->ptr, mlx->x, mlx->y);
	mlx->screen_data = mlx_get_data_addr(mlx->screen, &bpp, &size_line, &e);
	printf("textures\n");
	ft_init_textures(data);
	//ft_init_sprites(data);
	if (!mlx->ptr)
		ft_memory_error();
	if (!(mlx->window = mlx_new_window(mlx->ptr, mlx->x, mlx->y, map_name)))
		ft_memory_error();
}

void	ft_init_data(t_data *data, char *map_name, double rsp, double msp)
{
	t_player	*player;
	t_mlx		*mlx;

	printf("init_data\n");
	player = (t_player*)malloc(sizeof(t_player));
	mlx = (t_mlx*)malloc(sizeof(t_mlx));
	if (!player || !mlx)
		ft_memory_error();
	data->player = player;
	data->mlx = mlx;
	ft_init_player(player, rsp, msp);
	printf("get_map\n");
	ft_get_map(map_name, data);
	data->buffer_z = (double*)malloc(data->res_x * sizeof(double));
	if (!data->buffer_z)
		ft_memory_error();
	ft_init_mlx(data, map_name);
}

void	ft_loop(t_data *data)
{
	t_mlx *mlx;

	mlx = data->mlx;
	mlx_hook(mlx->window, 2, 1, ft_key_hook, data);
	mlx_hook(mlx->window, 3, 0, ft_key_release_hook, data);
	mlx_loop_hook(mlx->ptr, ft_loop_hook, data);
	printf("loop\n");
	mlx_loop(mlx->ptr);
}

int		main(int argc, char **argv)
{
	t_data		data;
	t_player	*p;

	ft_init_data(&data, "map.cub", 0.02, 0.1);
	(data.player)->kk = 0;
	p = data.player;
	printf("Rot_speed: %f\nMov_speed: %f\n", p->rot_speed, p->mov_speed);
	ft_render(&data, data.mlx, data.player, data.map);
	ft_loop(&data);
	return (0);
}
