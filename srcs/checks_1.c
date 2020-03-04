/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:47:41 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/04 18:52:30 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_check_n(char *str, t_data *data)
{
	if (str[0] != 'N' || str[1] != 'O' || !ft_isspace(str[2]))
		ft_cub_error();
	if (data->n)
		ft_cub_error();
	else
		data->n = 1;
	return (ft_set_dir_texture(str, 2, &(data->n_texture)));
}

int				ft_check_e(char *str, t_data *data)
{
	if (str[0] != 'E' || str[1] != 'A' || !ft_isspace(str[2]))
		ft_cub_error();
	if (data->e)
		ft_cub_error();
	else
		data->e = 1;
	return (ft_set_dir_texture(str, 2, &(data->e_texture)));
}

int				ft_check_w(char *str, t_data *data)
{
	if (str[0] != 'W' || str[1] != 'E' || !ft_isspace(str[2]))
		ft_cub_error();
	if (data->w)
		ft_cub_error();
	else
		data->w = 1;
	return (ft_set_dir_texture(str, 2, &(data->w_texture)));
}

int				ft_check_s(char *str, t_data *data)
{
	if (str[0] != 'S')
		ft_cub_error();
	if (str[1] == 'O' && ft_isspace(str[2]))
	{
		if (data->s)
			ft_cub_error();
		else
			data->s = 1;
		return (ft_set_dir_texture(str, 2, &(data->s_texture)));
	}
	if (str[1])
		return (ft_set_new_sprite(str, data));
	ft_cub_error();
	return (0);
}
