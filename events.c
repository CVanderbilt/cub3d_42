#include "cub3d.h"
/*
int				*g_map[] =
{
	(int[]){1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
 	(int[]){1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
 	(int[]){1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
 	(int[]){1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	(int[]){1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
 	(int[]){1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	(int[]){1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},		//-?
	(int[]){1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},		//^
	(int[]){1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},		//x
 	(int[]){1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},		//v
 	(int[]){1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},		//+
 	(int[]){1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}, //11
 	(int[]){1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
 	(int[]){1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1},
	(int[]){1,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,1},
 	(int[]){1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	(int[]){1,4,4,4,4,4,4,4,4,4,0,4,0,4,4,4,4,4,4,4,4,4,4,1},
	(int[]){1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	(int[]){1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	(int[]){1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	(int[]){1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	(int[]){1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	(int[]){1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	(int[]){1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};*/

	//key_hook(int keycode,void *param);
	//mouse_hook(int button,int x,int y,void *param);
	//loop_hook(void *param);

void	ft_print_map(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			printf("%d ", data->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
	printf("\n");
}

//mlx_int_param_KeyRelease
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

void	ft_move(t_data *data, t_player *player)
{
	float	step;
	float	a;

	step = player->mov_speed;
	//step = 1;
	a = player->rot_speed;
	//a = 0.157;
	if (player->moving_forward)
	{
		printf("deberia moverse\n");
		if (!data->map[(int)(player->x + player->dir_x * step)][(int)(player->y)])
			player->x += player->dir_x * step;
		if (!data->map[(int)(player->x)][(int)(player->y + player->dir_y * step)])
			player->y += player->dir_y * step;
	}
	if (player->moving_backward)
	{
		if (!data->map[(int)(player->x - player->dir_x * step)][(int)(player->y)])
			player->x -= player->dir_x * step;
		if (!data->map[(int)(player->x)][(int)(player->y - player->dir_y * step)])
			player->y -= player->dir_y * step;
	}
	if (player->moving_right)
	{
		if(!data->map[(int)(player->x - player->dir_y * step)][(int)(player->y)])
			player->x -= player->dir_y * step;
		if(!data->map[(int)(player->x)][(int)(player->y + player->dir_x * step)])
			player->y += player->dir_x * step;
	}
	if (player->moving_left)
	{
		if(!data->map[(int)(player->x + player->dir_y * step)][(int)(player->y)])
			player->x += player->dir_y * step;
		if(!data->map[(int)(player->x)][(int)(player->y - player->dir_x * step)])
			player->y -= player->dir_x * step;
	}
	if	(player->rotating_right)
	{
		player->x2 = player->dir_x;
		player->dir_x = player->dir_x * cos(a) - player->dir_y * sin(a);
		player->dir_y = player->x2 * sin(a) + player->dir_y * cos(a);
		player->x2 = player->plane_x;
		player->plane_x = player->plane_x * cos(a) - player->plane_y * sin(a);
		player->plane_y = player->x2 * sin(a) + player->plane_y * cos(a);
	}
	if (player->rotating_left)
	{
		a *= -1;
		player->x2 = player->dir_x;
		player->dir_x = player->dir_x * cos(a) - player->dir_y * sin(a);
		player->dir_y = player->x2 * sin(a) + player->dir_y * cos(a);
		player->x2 = player->plane_x;
		player->plane_x = player->plane_x * cos(a) - player->plane_y * sin(a);
		player->plane_y = player->x2 * sin(a) + player->plane_y * cos(a);
	}

	if (player->alpha >2 * M_PI)
		player->alpha -= 2 * M_PI;
	else if (player->alpha < 0)
		player->alpha += 2 * M_PI;
	printf("(x, y) (%f, %f)\n", player->x, player->y);
	printf("dir(x, y) (%f, %f)\n", player->dir_x, player->dir_y);
	printf("alpha: %f\n", player->alpha);
	printf("plane_x %f plane_y %f\n", player->plane_x, player->plane_y);


}

int		ft_loop_hook(void *params)
{
	t_data	*data;
	t_mlx	*mlx;

	data = (t_data *)params;
	mlx = data->mlx;
	mlx_clear_window (mlx->ptr, mlx->window);

	ft_move(data, data->player);

	return (ft_render(data, data->mlx, data->player, data->map));
}

int			ft_key_hook(int keycode, void *params)
{
	printf("pressed keycode: %d\n", keycode);
	ft_check_movement((t_data *)params, keycode, 1);
	return (0);
}

/*int		ft_key_hook(int keycode, void *params)
{
	t_data		*data;
	t_player	*player;
	t_mlx		*mlx;
	double		step;
	double		a;
	double		new_vector[2];
	
	data = (t_data *)params;
	player = data->player;
	mlx = data->mlx;
	//a = 0.157;
	printf("a: %f\nstep: %f\n", player->rot_speed, player->mov_speed);
	a = player->rot_speed;
	step = player->mov_speed;
	//step = 1.01;
	printf("keycode: %d\n", keycode);
	mlx_clear_window (mlx->ptr, mlx->window);
	if (keycode == 35)
	{
		ft_print_map(data);
	}
	if (keycode == 13)
	{
		//player->x += player->dir_x * 1.1;
		//player->y += player->dir_y * 1.1;
		if(!data->map[(int)(player->x + player->dir_x * step)][(int)(player->y)])
			player->x += player->dir_x * step;
		if(!data->map[(int)(player->x)][(int)(player->y + player->dir_y * step)])
			player->y += player->dir_y * step;
	}
	if (keycode == 1)
	{
		//player->x += player->dir_x * -1.1;
		//player->y += player->dir_y * -1.1;
		if(!data->map[(int)(player->x - player->dir_x * step)][(int)(player->y)])
			player->x -= player->dir_x * step;
		if(!data->map[(int)(player->x)][(int)(player->y - player->dir_y * step)])
			player->y -= player->dir_y * step;
	}
		//x' = x cos θ − y sin θ
	//y' = x sin θ + y cos θ
	if (keycode == 123)//124)
	{
		//both camera direction and camera plane must be rotated
		player->x2 = player->dir_x;
		player->dir_x = player->dir_x * cos(a) - player->dir_y * sin(a);
		player->dir_y = player->x2 * sin(a) + player->dir_y * cos(a);
		player->x2 = player->plane_x;
		player->plane_x = player->plane_x * cos(a) - player->plane_y * sin(a);
		player->plane_y = player->x2 * sin(a) + player->plane_y * cos(a);
	}
	
	if (keycode == 124)//123)
	{
		//both camera direction and camera plane must be rotated
		a *= -1;
		player->x2 = player->dir_x;
		player->dir_x = player->dir_x * cos(a) - player->dir_y * sin(a);
		player->dir_y = player->x2 * sin(a) + player->dir_y * cos(a);
		player->x2 = player->plane_x;
		player->plane_x = player->plane_x * cos(a) - player->plane_y * sin(a);
		player->plane_y = player->x2 * sin(a) + player->plane_y * cos(a);
	}

	if (keycode == 53)
	{
		printf("program ended");
		exit(0);
	}

	new_vector[0] = player->dir_y;
	new_vector[1] = player->dir_x;

	if (keycode == 0)
	{
		if(!data->map[(int)(player->x - player->dir_y * step)][(int)(player->y)])
			player->x -= player->dir_y * step;
		if(!data->map[(int)(player->x)][(int)(player->y + player->dir_x * step)])
			player->y += player->dir_x * step;
	}

	if (keycode == 2)
	{
		if(!data->map[(int)(player->x + player->dir_y * 1.01)][(int)(player->y)])
			player->x += player->dir_y * 1.01;
		if(!data->map[(int)(player->x)][(int)(player->y - player->dir_x * 1.01)])
			player->y -= player->dir_x * 1.01;
	}


	if (player->alpha >2 * M_PI)
		player->alpha -= 2 * M_PI;
	else if (player->alpha < 0)
		player->alpha += 2 * M_PI;
	printf("(x, y) (%f, %f)\n", player->x, player->y);
	printf("dir(x, y) (%f, %f)\n", player->dir_x, player->dir_y);
	printf("alpha: %f\n", player->alpha);
	printf("plane_x %f plane_y %f\n", player->plane_x, player->plane_y);
	//printf("\n\n");
	ft_render(data, data->mlx, data->player, data->map);
	if (keycode == 126)
	{
		printf("hecho\n\n");
		player->kk = 1;
	}
	//printf("\n\n");
	return (0);
}*/
/*
int		main(void)
{
	t_mlx		mlx;
	t_player	player;
	t_data		data;

	player.x = 11;
	player.y = 11;
	player.dir_x = 1;
	player.dir_y = 0;
	player.plane_x = 0;
	player.plane_y = 0.66;
	player.h = 0;
	if (!ft_init(&mlx, 500, 500, "tst"))
		return (1);

	data.player = &player;
	data.mlx = &mlx;
	//ft_render(&mlx, &player, g_map);
	
	mlx_loop_hook (mlx.ptr, ft_loop_hook, &data);
	mlx_key_hook (mlx.window, ft_key_hook, &data);

	mlx_loop(mlx.ptr);
	return (0);
}*/
