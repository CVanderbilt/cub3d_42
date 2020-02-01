/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 10:43:11 by eherrero          #+#    #+#             */
/*   Updated: 2020/02/01 14:37:28 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_player(t_player *player, double r_speed, double m_speed)
{
	//printf("init_player\n");
	//printf("r_speed: %f\nm_speed: %f\n", r_speed, m_speed);
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
	//printf("path: >%s<\n", path);
	fd = open(path, O_RDONLY);
	get_next_line(fd, &line);
	//printf("readed 0 >%s<\n", line);
//	printf("  free(ft_init-texture) %p\n", line);
	free(line);
	get_next_line(fd, &line);
	//printf("readed 1>%s<\n", line);
//	printf("  free(ft_init_texture0) %p\n", line);
	free(line);
	get_next_line(fd, &line);
	//printf("readed 2>%s<\n", line);
//	printf("  free(ft_init_texture1) %p\n", line);
	free(line);
	get_next_line(fd, &line);
	//close(fd);
	fd = 0;
	//printf("readed 3>%s<\n\n", line);
	while (!ft_isdigit(line[fd]))
		fd++;
	//printf("width\nfd: %d\nline: %s\n", fd, line + fd);
	t->width = ft_atoi(line + fd);
	//printf("width: %d\n", t->width);
	while (ft_isdigit(line[fd]))
		fd++;
	while (!ft_isdigit(line[fd]))
		fd++;
	t->height = ft_atoi(line + fd);
	//printf("height %d\n", t->height);
	t->bpp = 4;
	t->size_line = t->bpp * t->width;
	//printf("image and addr\n");
	t->img = mlx_xpm_file_to_image(mlx->ptr, path, &(t->width), &(t->height));
	t->addr = (int *)mlx_get_data_addr(t->img, &(t->bpp), &(t->size_line), &e);
	//printf("end\n");
//	printf("  free(ft_init_texture2) %p\n", line);
	free(line);
	while (get_next_line(fd, &line) > 0)
		{
//			printf("  free(ft_init_texture3) %p\n", line);
			free(line);
		}
	//printf("  free(ft_init_texture4) %p\n", line);
	free(line);
	close(fd);
}

void	ft_init_textures(t_data *data)
{
	t_mlx	*mlx;

	mlx = data->mlx;
	mlx->n_img = (t_texture*)malloc(sizeof(t_texture));
//	printf("malloc(ft_init_textures) %p\n", mlx->n_img);
	mlx->s_img = (t_texture*)malloc(sizeof(t_texture));
//	printf("malloc(ft_init_textures) %p\n", mlx->s_img);
	mlx->w_img = (t_texture*)malloc(sizeof(t_texture));
//	printf("malloc(ft_init_textures) %p\n", mlx->w_img);
	mlx->e_img = (t_texture*)malloc(sizeof(t_texture));
//	printf("malloc(ft_init_textures) %p\n", mlx->e_img);
	mlx->skybox = (t_texture*)malloc(sizeof(t_texture));
//	printf("malloc(ft_init_textures) %p\n", mlx->skybox);
	//mlx->sprite1 = (t_texture*)malloc(sizeof(t_texture));
	//mlx->floor = (t_texture*)malloc(sizeof(t_texture));
	if (!mlx->n_img || !mlx->s_img || !mlx->e_img || !mlx->w_img
			|| !mlx->skybox)
		ft_memory_error();
	ft_init_texture(mlx, mlx->n_img, "brick.xpm");
	ft_init_texture(mlx, mlx->s_img, "stone.xpm");
	ft_init_texture(mlx, mlx->e_img, "metal.xpm");
	ft_init_texture(mlx, mlx->w_img, "wood.xpm");
	ft_init_texture(mlx, mlx->skybox, "skybox.xpm");
	//ft_init_texture(mlx, mlx->sprite1, "sprite.xpm");
	//ft_init_texture(mlx, mlx->floor, "wood.xpm");
}

void	ft_init_sprites(t_data *data)
{
	int			i;
	t_sprite	*s;

	//printf("init sprites:\n");
	i = 0;
	s = data->sprite_buffer;
	while (i < data->sprites_num)
	{
	//	printf("sprite %d: %s\n", i, s[i].texture_path);
		//s[i].texture = (t_texture*)malloc(sizeof(t_texture));
//		printf("malloc(ft_init_sprites) %p\n", s[i].texture);
		//ft_init_texture(data->mlx, s[i].texture, s[i].texture_path);
		i++;
	}
	//exit(0);
}

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
	//printf("init_mlx: %p\n", mlx);
	mlx->x = data->res_x > 0 ? data->res_x : 500;
	mlx->y = data->res_y > 0 ? data->res_y : 500;
	//printf("ptr\n");
	//if (!(mlx->ptr = mlx_init()))
	//	ft_memory_error();
	//getchar();
	printf("mlx_image 1\n");
	mlx->screen = mlx_new_image(mlx->ptr, mlx->x, mlx->y);
	printf("mlx_image 2\n");
	mlx->screen_data = mlx_get_data_addr(mlx->screen, &bpp, &size_line, &e);
	//printf("init_mlx 3\n");
	//printf("textures\n");
	ft_init_textures(data);
	//getchar();
	//printf("init_mlx 4\n");
	//ft_init_sprites(data);
	//printf("init_mlx 5\n");
	if (!mlx->ptr)
		ft_memory_error();
	//printf("init_mlx 6\n");
	printf("mlx_ptr %p, mlx_y %d, mlx_y %d, name %s\n", mlx->ptr, mlx->x, mlx->y, map_name);
	printf("mlx_window\n");
	//getchar();
	if (!(mlx->window = mlx_new_window(mlx->ptr, mlx->x, mlx->y, map_name)))
		ft_memory_error();
	printf("mlx_window\n");
	//printf("init_mlx 7\n");
}

void	ft_init_data(t_data *data, char *map_name, double rsp, double msp)
{
	t_player	*player;
	t_mlx		*mlx;

	//printf("init_data\n");
	player = (t_player*)malloc(sizeof(t_player));
//	printf("malloc(ft_init_data) %p\n", player);
	mlx = (t_mlx*)malloc(sizeof(t_mlx));
//	printf("malloc(ft_init_data) %p\n", mlx);
	if (!player || !mlx)
		ft_memory_error();
	//getchar();
	printf("movido aqui\n");
	mlx->ptr = mlx_init();
	printf("sigue\n");
	data->player = player;
	data->mlx = mlx;
	ft_init_player(player, rsp, msp);
	//getchar();
	data->sprite_buffer = 0;
	data->sprites_num = 0;
	data->sprite_tex_buffer = 0;
	data->sprite_tex_num = 0;
	//data
	printf("get_map\n");
	ft_get_map(map_name, data);
	data->buffer_z = (double*)malloc(data->res_x * sizeof(double));
	//getchar();
//	printf("malloc(ft_init_data) %p\n", data->buffer_z);
	if (!data->buffer_z)
		ft_memory_error();
	//getchar();
	data->hud = (t_texture*)malloc(sizeof(t_texture));
	if (!data->hud)
		ft_memory_error();
	ft_init_texture(data->mlx, data->hud, "hud.xpm");
	ft_init_mlx(data, map_name);
	/////getchar();
}

void	ft_loop(t_data *data)
{
	t_mlx *mlx;

	//printf("start_loop");
	mlx = data->mlx;
	mlx_hook(mlx->window, 2, 1, ft_key_hook, data);
	mlx_hook(mlx->window, 3, 0, ft_key_release_hook, data);
	mlx_loop_hook(mlx->ptr, ft_loop_hook, data);
	//printf("end_loop\n");
	printf("mlx->ptr %p\n", mlx->ptr);
	printf("entra mlx_loop\n");
	mlx_loop(mlx->ptr);
}

int		main(int argc, char **argv)
{
	t_data		data;
	t_player	*p;

	//data.sprites_num = 2;
	ft_init_data(&data, "map.cub", 0.02, 0.1);


	//printf("sprites: %d\n", data.sprites_num);
	//printf("sprite: %p\n", data.sprite_buffer);
	//printf("  path1: %s\n", data.sprite_buffer[0].texture_path);
	//printf("  x: %f, y: %f\n", data.sprite_buffer[0].x, data.sprite_buffer[0].y);
	//printf("sprite: %p\n", &data.sprite_buffer[1]);
	//printf("  path2: %s\n", data.sprite_buffer[1].texture_path);
	//printf("  x: %f, y: %f\n", data.sprite_buffer[1].x, data.sprite_buffer[1].y);
	(data.player)->kk = 0;
	p = data.player;
	//printf("Rot_speed: %f\nMov_speed: %f\n", p->rot_speed, p->mov_speed);
	printf("start_first_render\n");
	/*int i = -1;
	while (++i < data.sprite_tex_num)
	{
		printf("tex %d: %d\n", i, data.sprite_tex_buffer[i].width);
	}*/
	ft_render(&data, data.mlx, data.player, data.map);
	printf("end_first_render\n");
	ft_loop(&data);
	return (0);
}
