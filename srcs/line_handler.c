/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:46:58 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/09 16:46:00 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_first_line_check(int *line, int **tab, char *str, t_data *d)
{
	t_first_line_check	ft;
	int					*row;

	ft.i = -1;
	ft.count = 0;
	str[0] = str[0] != '1' && str[0] != ' ' ? ft_map_error() : str[0];
	while (str[++ft.i])
		if (str[ft.i] == '1' || str[ft.i] == ' ')
			ft.count++;
	row = (int *)malloc(sizeof(int) * ft.count);
	d->map_width = !row ? ft_memory_error() : ft.count;
	tab[0] = row;
	ft.i = 0;
	while (ft.i < d->map_width && str[ft.i])
	{
		tab[0][ft.i] = str[ft.i] == '1' ? 1 : 3;
		ft.i++;
	}
	*line = 1;
	return (0);
}

void			ft_check_map_line_aux(t_check_map_line *ft,
		int *l, t_data *data, char *s)
{
	while (s[ft->i])
	{
		if (!ft_isdigit(s[ft->i]) && !ft_isspace(s[ft->i]))
			ft_set_pos(data->player, s[ft->i], ft->i, *l);
		data->map[*l][ft->count] = !ft_isdigit(s[ft->i]) ? 0 : s[ft->i] - 48;
		data->map[*l][ft->count] += !ft_isspace(s[ft->i]) ? 0 : 3;
		if ((data->map[*l][ft->count] < 0 || data->map[*l][ft->count] > 3)
				&& data->map[*l][ft->count] != ' ')
			ft_map_error();
		if (data->map[*l][ft->count] == 2)
		{
			ft_set_map_sprite(*l, ft->count, data);
			data->map[*l][ft->count] = 0;
		}
		ft_check_space_valid(data->map, *l, ft->count, data->map_width);
		ft->count++;
		ft->last_element = s[ft->i++];
	}
	ft_fill_line(ft, data, l);
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
	data->map = tab;
	ft_check_map_line_aux(&ft, line, data, str);
	ft.last_element = ft.last_element == ' ' ? '1' : ft.last_element;
	*line = ft.last_element != '1' ? ft_map_error() : *line + 1;
	return (ft_check_full(str, '1'));
}

int				ft_check_line(int *line, int **tab, char *str, t_data *data)
{
	write(1, "line(fcl): ", 11);
	ft_putstr(str);
	write(1, "\n", 1);
	if (str[0] != '1')
	{
		if (*line || str[0] == ' ')
			return (ft_check_map_line(line, tab, str, data));
		else
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
	ft.fd = ft_open_check(map, O_RDONLY);
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
	if (!data->n || !data->s || !data->e || !data->w)
		ft_cub_error();
	free(ft.str);
	data->map = t;
	data->map_height = l;
	return (ft.finished ? 1 : ft_map_error());
}
