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
	printf("this works\n");
	return (0);
}

int		ft_loop_hook(void *params)
{
	t_data	*data;
	t_mlx	*mlx;

	data = (t_data *)params;
	mlx = data->mlx;
	mlx_clear_window (mlx->ptr, mlx->window);
	return (ft_render(data, data->mlx, data->player, data->map));
}

int		ft_key_hook(int keycode, void *params)
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
	/*
	if (keycode == 124)
	{
		new_vector[0] = player->dir_y;
		new_vector[1] = player->dir_x * -1;
		printf("move at dir_x %f dir_y %f\n", new_vector[0], new_vector[1]);
		player->x += new_vector[0] * 1.1;
		player->y += new_vector[1] * 1.1;
	}

	if (keycode == 123)
	{
		new_vector[0] = player->dir_y;
		new_vector[1] = player->dir_x;
		printf("move at dir_x %f dir_y %f\n", new_vector[0], new_vector[1]);
		player->y += player->dir_x * 1.1;
		player->x += player->dir_y * 1.1;
	}
	*/
	//x' = x cos θ − y sin θ
	//y' = x sin θ + y cos θ
	if (keycode == 123)//124)
	{
		//player->x += player->dir_y * 1.1;
		//player->y += player->dir_x * 1.1;
		//player->x2 = player->dir_x * cos(a) - player->dir_y * sin(a);
		//player->y2 = player->dir_x * sin(a) + player->dir_y * cos(a);
		/*
		player->x2 = player->alpha;
		player->y2 = player->plane_x;
		player->alpha += a;
		player->dir_x = cos(player->alpha);
		player->dir_y = sin(player->alpha);
		player->plane_x = player->plane_x * cos(a) - player->plane_y * cos(a);
		player->plane_y = player->x2 * sin(a) + player->plane_y * cos(a);
*/
		//both camera direction and camera plane must be rotated
		player->x2 = player->dir_x;
		player->dir_x = player->dir_x * cos(a) - player->dir_y * sin(a);
		player->dir_y = player->x2 * sin(a) + player->dir_y * cos(a);
		player->x2 = player->plane_x;
		player->plane_x = player->plane_x * cos(a) - player->plane_y * sin(a);
		player->plane_y = player->x2 * sin(a) + player->plane_y * cos(a);

/*double oldDirX = dirX;
dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
double oldPlaneX = planeX;
planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);*/




	}
	
	if (keycode == 124)//123)
	{
		//player->x += player->dir_y * -1.1;
		//player->y += player->dir_x * -1.1;
		//player->x2 = player->dir_x * cos(a) - player->dir_y * sin(a);
		//player->y2 = player->dir_x * sin(a) + player->dir_y * cos(a);
/*		
		a *= -1;
		player->x2 = player->alpha;
		player->y2 = player->plane_x;
		player->alpha += a;
		player->dir_x = cos(player->alpha);
		player->dir_y = sin(player->alpha);
		player->plane_x = player->plane_x * cos(a) - player->plane_y * cos(a);
		player->plane_y = player->x2 * sin(a) + player->plane_y * cos(a);
	*/	

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

//params->pl->pos_y += params->pl->dir_x * speed;
//		params->pl->pos_x -= params->pl->dir_y * speed;

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
}
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
