#include "cub3d.h"
/*
typedef struct	s_player
{
	//player pos.
	double		x;
	double		y;
	//player dir.
	double		dir_x;
	double		x2;//aux
	double		dir_y;
	double		y2;//aux
	//camera plane.
	double		plane_x;
	double		plane_y;
	//player stats
	int			h;//h modifier for render (jump and crawl)
	double		moveSpeed;// = frameTime * 5.0; //the constant value is in squares/second
    double		rotSpeed;// = frameTime * 3.0; //the constant value is in radians/second
}				t_player;

typedef struct	s_data
{
	//t_mlx		*mlx;
	t_player	*player;
	int			**map;
	int			map_width;
	int			map_height;
	int			res_x;
	int			res_y;
	char		*n_texture;
	char		*s_texture;
	char		*w_texture;
	char		*e_texture;
	char		*sprite_texture;
	int			floor_color;
	int			ceil_color;
}				t_data;
*/
void	ft_print_data(t_data *data)
{
	t_player *p;

	p = data->player;
	printf("player: %p\n", data->player);
	printf("  x: %+f\n  y: %+f\n  dir_x %+f\n  dir_y %+f\n", p->x, p->y, p->dir_x, p->dir_y);
	printf("map: %p\n", data->map);
	printf("  width: %d\n", data->map_width);
	printf("  height: %d\n", data->map_height);
	printf("  res_x: %d\n", data->res_x);
	printf("  res_y: %d\n", data->res_y);

	printf("  n_texture: %s\n", data->n_texture);
	printf("  s_texture: %s\n", data->s_texture);
	printf("  w_texture: %s\n", data->w_texture);
	printf("  e_texture: %s\n", data->e_texture);
	printf("  sprite_texture: %s\n", data->sprite_texture);
	printf("floor color %d\n", data->floor_color);
	printf("ceiling color %d\n", data->ceil_color);
}

//calloc start
static void	ft_kk(void *s, size_t n)
{
	char *i;

	i = (char*)s;
	while (n > 0)
	{
		*(i++) = 0;
		n--;
	}
}

int			ft_memory_error()
{
	write(1, "memory error\n", 13);
	exit(EXIT_FAILURE);
	return (0);
}

int			ft_map_error()
{
	write(1, "map error\n", 10);
	exit(EXIT_FAILURE);
	return (0);
}

int			ft_cub_error()
{
	write(1, "cub error\n", 10);
	exit(EXIT_FAILURE);
	return (0);
}

void		*ft_calloc(size_t count, size_t size)
{
	void *p;

	if (!(p = malloc(count * size)))
		return (0);
	ft_kk(p, count * size);
	return (p);
}

void	*ft_realloc(void *ptr, int prev_size, int new_size)
{
	char 	*str;
	char	*ret;
	int		i;

	//printf("realoc:\n");
	//printf("str: %s\n", (char *)ptr);
	//printf("prev_size: %d\nnew_size: %d\n", prev_size, new_size);
	if (!ptr || prev_size <= 0 || new_size <= 0)
		return (0);
	i = 0;
	str = (char *)ptr;
	ret = ft_calloc(new_size, sizeof(char));
	if (!ret)
		return (0);
	while (i < prev_size)
	{
		ret[i] = str[i];
		i++;
	}
	free(str);
	return ((void *)ret);
}

int		ft_in_set(char c, char *set)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (*set == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_set_pos(t_player *player, char c, int x, int y)
{
	float	rect;

	rect = 1.57;
	if (player->x != 0 || player->y != 0)
		ft_map_error();
	player->y = (double)x + 0.5;
	player->x = (double)y + 0.5;
	if (c == 'N' || c == 'S')
	{
		player->dir_y = 0;
		player->dir_x = c != 'N' ? 1 : -1;
		player->alpha = c != 'N' ? rect * 2 : rect * 4;
		player->plane_x = 0;
		player->plane_y = c != 'N' ? 0.66 : -0.66;
	}
	else if (c == 'E' || c == 'W')
	{
		player->dir_x = 0;
		player->dir_y = c == 'E' ? 1 : -1;
		player->alpha = c == 'E' ? rect * 1 : rect * 3;
		player->plane_y = 0;
		player->plane_x = c == 'E' ? -0.66 : 0.66;
	}
	else
		ft_map_error();
}

int		ft_check_full(char *str, char c)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] != c)
			return (0);
	return (1);
}

int		ft_set_dir_texture(char *str, int i, char **texture)
{
	int		j;
	int		k;
	char	*ret;	

	k = 0;
	while (ft_isspace(str[i]))
		i++;
	if (!str[i])
		ft_cub_error();
	j = i;
	while (!ft_isspace(str[i]))
		i++;
	ret = (char *)malloc(i - j + 1);
	if (!ret)
	{
		printf("1\n");
		ft_memory_error();
	}
	while (j < i)
		ret[k++] = str[j++];
	*texture = ret;
	return (0);
}

int		ft_check_n(char *str, t_data *data)
{
	if (str[0] != 'N' || str[1] != 'O' || !ft_isspace(str[2]))
		ft_cub_error();
	return (ft_set_dir_texture(str, 2, &(data->n_texture)));
}

int		ft_check_e(char *str, t_data *data)
{
	if (str[0] != 'E' || str[1] != 'A' || !ft_isspace(str[2]))
	   ft_cub_error();
	return (ft_set_dir_texture(str, 2, &(data->e_texture)));	
}

int		ft_check_w(char *str, t_data *data)
{
	if (str[0] != 'W' || str[1] != 'E' || !ft_isspace(str[2]))
	   ft_cub_error();
	return (ft_set_dir_texture(str, 2, &(data->w_texture)));	
}

int		ft_check_s(char *str, t_data *data)
{
	//printf("check_s\n");
	if (str[0] != 'S')
	   ft_cub_error();
	else
		if (str[1] == 'O' && ft_isspace(str[2]))
			return (ft_set_dir_texture(str, 2, &(data->s_texture)));
	if (ft_isspace(str[1]))
		return (ft_set_dir_texture(str, 1, &(data->sprite_texture)));
	ft_cub_error();
	return (0);
}

int		ft_check_r(char *str, t_data *data)
{
	int i;

	i = 1;
	if (str[0] != 'R' || !ft_isspace(str[1]))
		ft_cub_error();
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		ft_cub_error();
	data->res_x = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	if (!ft_isspace(str[i]))
		ft_cub_error();
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		ft_cub_error();
	data->res_y = ft_atoi(str + i);
	if (!(data->res_x) || !(data->res_y))
	   ft_cub_error();
	return (0);	
}

void	ft_atoi_rgb(char *str, int rgb[3])
{
	int	i;

	i = 1;
	if (!ft_isspace(str[1]))
		ft_cub_error();
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		ft_cub_error();
	rgb[0] = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ',' && !ft_isdigit(str[i + 1]))
		ft_cub_error();
	rgb[1] = ft_atoi(str + i + 1);
	i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ',' && !ft_isdigit(str[i + 1]))
		ft_cub_error();
	rgb[2] = ft_atoi(str + i + 1);
}

int		ft_check_c(char *str, t_data *data)
{
	int rgb[3];
	int	*p;

	
	if ((str[0] == 'C' || str[0] == 'F') && ft_isspace(str[1]))
		p = str[0] == 'C' ? &(data->ceil_color) : &(data->floor_color);
	else
		ft_cub_error();
	ft_atoi_rgb(str, rgb);
	if (rgb[0] > 255 || rgb[0] < 0)
		ft_cub_error();
	if (rgb[1] > 255 || rgb[1] < 0)
		ft_cub_error();
	if (rgb[2] > 255 || rgb[2] < 0)
		ft_cub_error();
	*p = rgb[0] * 65536 + rgb[1] * 256 + rgb[2];
	return (0);
}

int		ft_check_info_line(char *str, t_data *data)
{
	//printf("str: %s\n", str);
	if (str[0] == 'R')
		return (ft_check_r(str, data));
	if (str[0] == 'N')
		return (ft_check_n(str, data));
	if (str[0] == 'S')
		return (ft_check_s(str, data));
	if (str[0] == 'W')
		return (ft_check_w(str, data));
	if (str[0] == 'E')
		return (ft_check_e(str, data));
	if (str[0] == 'C' || str[0] == 'F')
		return (ft_check_c(str, data));
	if (!str[0])
		return (0);
	return (ft_cub_error());
}

int		ft_first_line_check(int *line, int **tab, char *str, t_data *data)
{
	int i;
	int count;
	int	*row;
	
	i = 0;
	count = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] != '1')
		ft_map_error();
	while (str[i])
	{
		if (str[i] == '1')
			count++;
		else if (!ft_isspace(str[i]))
			return (ft_map_error());
		i++;
	}
	//printf("width: %d\n", i);
	data->map_width = count;
	row = (int *)malloc(sizeof(int) * i);
	if (!row)
	{
		printf("2\n");
		return (ft_memory_error());
	}
	tab[0] = row;
	i = 0;
	while (i < data->map_width && str[i])
	{
		tab[0][i] = 1;
		i++;
	}
	*line = 1;
	return (0);
}

int		ft_check_map_line(int *line, int **tab, char *str, t_data *data)
{
	t_player	*player;
	int			*row;
	int			i;
	int			count;
	int			last_element;

	i = 0;
	//count = data->map_width;
	count = 0;
	last_element = 0;
	if (*line == 0)
		return (ft_first_line_check(line, tab, str, data));


	//printf("reservamos para row: ->4 * %d\n", data->map_width);
	row = (int *)malloc(sizeof(int) * data->map_width);
	if (!row)
	{
		printf("3\n");
		ft_memory_error();
	}
	//printf("mem reserved: %p\n", row);
	tab[*line] = row;
	player = data->player;
	//printf("line: %s\n", str);
	while (ft_isspace(str[i]))
	{
		//printf("space (%c)\n", str[i]);
		i++;
	}
	//printf("str[i] = %c\n", str[i]);
	if (str[i] != '1')
	{
		printf("kk\n");
		ft_map_error();
	}
	
	//printf("while: (%d)", *line);
	while (str[i])
	{
		//printf("  str[i]: %c\n", str[i]);
		if (!ft_isdigit(str[i]) && !ft_isspace(str[i]))
		{
			ft_set_pos(player, str[i], i, *line);
			tab[*line][count] = 0;
			//count--;
			count++;
			//printf("  [%d][%d]: %d\n", *line, i, 0);
		}
		else if (!ft_isspace(str[i]))
		{
			tab[*line][count] = str[i] - 48;
			last_element = str[i];
			//printf("  last element: %c\n", last_element);
			//count--;
			count++;
			printf("  [%d][%d]: %d\n", *line, i, str[i] - 48);
		}
		i++;
	}
	if (last_element != '1')
	{
		//printf("last element: %c\n", last_element);
		ft_map_error();
	}
	*line = *line + 1;;
	return (ft_check_full(str, '1'));
}

int		ft_check_line(int *line, int **tab, char *str, t_data *data)
{
	printf("line(fcl): %s\n", str);
	if (str[0] != '1')
	{
	//	printf("line: %d\n", *line);
		return (!(*line) ? ft_check_info_line(str, data) : -1);
	}
	return (ft_check_map_line(line, tab, str, data));
}

int		ft_get_map(char *map, t_data *data)
{
	int		fd;
	int		line;
	int		finished;
	int		**tab;
	char	*str;

	tab = (int **)malloc(sizeof(int *) * 20);
	if (tab == 0)
	{
		printf("4\n");
		return (ft_memory_error());
	}
	line = 0;
	finished = 0;
	fd = open(map, O_RDONLY);
	while (get_next_line(fd, &str))
	{
		//printf("RESERVA\n");
		if ((finished = ft_check_line(&line, tab, str, data)) < 0)
			ft_map_error();
		if (line && !(line % 20))
		{
			//printf("tab dir: %p\n", tab);
			tab = (int **)ft_realloc(tab, line * sizeof(int *), (line + 20) * sizeof(int *));
			if (!tab)
			{
				printf("5\n");
				return (ft_memory_error());
			 }
			//printf("new tab dir: %p\n", tab);
		}
		//printf("LIBERA\n");
		free(str);
	}
	free(str);
	data->map = tab;
	data->map_height = line;
	return (finished ? 1 : ft_map_error());
}
/*
int main()
{
	t_player	player;
	t_data		data;
	int i;
	int j;

	player.x = 0;
	player.y = 0;
	data.player = &player;
	ft_get_map("map.cub", &data);

	i = 0;
	j = 0;
	printf("tab:\n");
	while (i < data.map_height)
	{
		printf("row: %3d: ", i);
		printf("dir: %p ", data.map[i]);
		while (j < data.map_width)
		{
			printf("%d ", data.map[i][j]);
			j++;
		}
		printf("\n");
		j = 0;
		i++;
	}

	printf("data:\n");
	ft_print_data(&data);
	return (0);
}*/
