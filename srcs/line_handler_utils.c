/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handler_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:55:23 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/09 15:17:40 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_set_map_sprite(int x, int y, t_data *data)
{
	char	*str1;
	char	*str2;
	char	*str3;

	str1 = ft_itoa(x);
	str2 = ft_strjoin("S ", str1);
	free(str1);
	str1 = ft_strjoin(str2, " ");
	free(str2);
	str2 = ft_itoa(y);
	str3 = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	str2 = ft_strjoin(str3, " 0 H 1 0");
	free(str3);
	ft_set_new_sprite(str2, data);
	free(str2);
	return (1);
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
	if (str[0] == 'T')
		return (ft_set_new_sprite(str, data));
	if (!str[0])
		return (0);
	return (ft_cub_error());
}

void			ft_validate_coordinate(t_coordinate c, int s, int **t, int c1)
{
	int comp2;

	if (c.x < 0 || c.y < 0 || c.y >= s)
		return ;
	comp2 = t[c.x][c.y];
	if (comp2 != 1 && comp2 != c1)
		ft_map_error();
}

void			ft_check_space_valid(int **tab, int x, int y, int size)
{
	int				comp;
	t_coordinate	c;

	c.x = x;
	c.y = y;
	if (c.x < 0 || c.y < 0 || c.y >= size)
		ft_cub_error();
	comp = tab[c.x][c.y];
	if (comp == 1)
		return ;
	c.y--;
	ft_validate_coordinate(c, size, tab, comp);
	c.x--;
	ft_validate_coordinate(c, size, tab, comp);
	c.y++;
	ft_validate_coordinate(c, size, tab, comp);
	c.y++;
	ft_validate_coordinate(c, size, tab, comp);
}

void			ft_fill_line(t_check_map_line *ft, t_data *data, int *l)
{
	if (ft->count < data->map_width)
	{
		while (ft->count < data->map_width)
		{
			data->map[*l][ft->count] = 3;
			ft_check_space_valid(data->map, *l, ft->count, data->map_width);
			ft->count++;
		}
		ft->last_element = ' ';
	}
}
