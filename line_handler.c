/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:46:58 by eherrero          #+#    #+#             */
/*   Updated: 2020/02/25 11:50:04 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (str[0] == 'T')
		return (ft_check_t(str, data));
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
	row = (int *)malloc(sizeof(int) * ft.count);
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

	ft.count = 0;
	ft.last_element = 0;
	if (((ft.i = 0) || 1) && *line == 0)
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
	if (ft.count != data->map_width)
		ft_cub_error();
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
