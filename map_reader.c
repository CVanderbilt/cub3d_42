/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:15:57 by eherrero          #+#    #+#             */
/*   Updated: 2020/01/28 16:46:22 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		ft_kk(void *s, size_t n)
{
	char *i;

	i = (char*)s;
	while (n > 0)
	{
		*(i++) = 0;
		n--;
	}
}

int				ft_memory_error(void)
{
	write(1, "memory error\n", 13);
	exit(EXIT_FAILURE);
	return (0);
}

int				ft_map_error(void)
{
	write(1, "map error\n", 10);
	exit(EXIT_FAILURE);
	return (0);
}

int				ft_cub_error(void)
{
	write(1, "cub error\n", 10);
	exit(EXIT_FAILURE);
	return (0);
}

void			*ft_calloc(size_t count, size_t size)
{
	void *p;

	if (!(p = malloc(count * size)))
		return (0);
	ft_kk(p, count * size);
	return (p);
}

void			*ft_realloc(void *ptr, int prev_size, int new_size)
{
	char	*str;
	char	*ret;
	int		i;

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

int				ft_in_set(char c, char *set)
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

void			ft_set_pos(t_player *player, char c, int x, int y)
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
		//player->alpha = c != 'N' ? rect * 2 : rect * 4;
		player->plane_x = 0;
		player->plane_y = c != 'N' ? 0.66 : -0.66;
	}
	else if (c == 'E' || c == 'W')
	{
		player->dir_x = 0;
		player->dir_y = c == 'E' ? 1 : -1;
		//player->alpha = c == 'E' ? rect * 1 : rect * 3;
		player->plane_y = 0;
		player->plane_x = c == 'E' ? -0.66 : 0.66;
	}
	else
		ft_map_error();
}

int				ft_check_full(char *str, char c)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] != c)
			return (0);
	return (1);
}

int				ft_set_dir_texture(char *str, int i, char **texture)
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

int				ft_check_n(char *str, t_data *data)
{
	if (str[0] != 'N' || str[1] != 'O' || !ft_isspace(str[2]))
		ft_cub_error();
	return (ft_set_dir_texture(str, 2, &(data->n_texture)));
}

int				ft_check_e(char *str, t_data *data)
{
	if (str[0] != 'E' || str[1] != 'A' || !ft_isspace(str[2]))
		ft_cub_error();
	return (ft_set_dir_texture(str, 2, &(data->e_texture)));
}

int				ft_check_w(char *str, t_data *data)
{
	if (str[0] != 'W' || str[1] != 'E' || !ft_isspace(str[2]))
		ft_cub_error();
	return (ft_set_dir_texture(str, 2, &(data->w_texture)));
}

int				ft_check_s(char *str, t_data *data)
{
	if (str[0] != 'S')
		ft_cub_error();
	else if (str[1] == 'O' && ft_isspace(str[2]))
		return (ft_set_dir_texture(str, 2, &(data->s_texture)));
	if (ft_isspace(str[1]))
		return (ft_set_dir_texture(str, 1, &(data->sprite_texture)));
	ft_cub_error();
	return (0);
}

int				ft_check_r(char *str, t_data *data)
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

void			ft_atoi_rgb(char *str, int rgb[3])
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

int				ft_check_c(char *str, t_data *data)
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

int				ft_check_info_line(char *str, t_data *data)
{
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

int				ft_first_line_check(int *line, int **tab, char *str, t_data *d)
{
	t_first_line_check	ft;
	int					*row;

	ft.i = 0;
	ft.count = 0;
	str[ft.i] = str[ft.i] != '1' ? ft_map_error() : str[ft.i];
	while (str[ft.i])
	{
		if (str[ft.i] == '1')
			ft.count++;
		else if (!ft_isspace(str[ft.i]))
			return (ft_map_error());
		ft.i++;
	}
	row = (int *)malloc(sizeof(int) * ft.i);
	d->map_width = !row ? ft_memory_error() : ft.count;
	tab[0] = row;
	ft.i = 0;
	while (ft.i < d->map_width && str[ft.i])
	{
		tab[0][ft.i] = 1;
		ft.i++;
	}
	*line = 1;
	return (0);
}

int				ft_check_map_line(int *line, int **tab, char *str, t_data *data)
{
	int					*row;
	t_check_map_line	ft;

	ft.i = 0;
	ft.count = 0;
	ft.last_element = 0;
	if (*line == 0)
		return (ft_first_line_check(line, tab, str, data));
	if (!(row = (int *)malloc(sizeof(int) * data->map_width)))
		ft_memory_error();
	tab[*line] = row;
	while (ft_isspace(str[ft.i]))
		ft.i++;
	str[ft.i] = str[ft.i] != '1' ? ft_map_error() : str[ft.i];
	while (str[ft.i])
	{
		if (!ft_isdigit(str[ft.i]) && !ft_isspace(str[ft.i]))
			ft_set_pos(data->player, str[ft.i], ft.i, *line);
		tab[*line][ft.count] = !ft_isdigit(str[ft.i]) ? 0 : str[ft.i] - 48;
		ft.count += !ft_isspace(str[ft.i]) ? 1 : 0;
		ft.last_element = str[ft.i++];
	}
	*line = ft.last_element != '1' ? ft_map_error() : *line + 1;
	return (ft_check_full(str, '1'));
}

int				ft_check_line(int *line, int **tab, char *str, t_data *data)
{
	printf("line(fcl): %s\n", str);
	if (str[0] != '1')
	{
		return (!(*line) ? ft_check_info_line(str, data) : -1);
	}
	return (ft_check_map_line(line, tab, str, data));
}

int				ft_get_map(char *map, t_data *data)
{
	int				l;
	int				**t;
	t_check_line	ft;

	if (!(t = (int **)malloc(sizeof(int *) * 20)))
		return (ft_memory_error());
	l = 0;
	ft.finished = 0;
	ft.fd = open(map, O_RDONLY);
	while (get_next_line(ft.fd, &(ft.str)))
	{
		if ((ft.finished = ft_check_line(&l, t, ft.str, data)) < 0)
			ft_map_error();
		if (l && !(l % 20))
			if (!(t = ft_realloc(t, l * sizeof(int *),
							(l + 20) * sizeof(int *))))
				return (ft_memory_error());
		free(ft.str);
	}
	free(ft.str);
	data->map = t;
	data->map_height = l;
	return (ft.finished ? 1 : ft_map_error());
}
