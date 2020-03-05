/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:48:42 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/05 14:50:56 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (data->res_x <= 0 || (data->res_y <= 0))
		ft_cub_error();
	data->res_x = data->res_x > 1024 ? 1024 : data->res_x;
	data->res_y = data->res_y > 1024 ? 1024 : data->res_y;
	return (0);
}

int				ft_check_c(char *str, t_data *data)
{
	int rgb[3];
	int	*p;

	p = 0;
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

int				ft_check_t(char *str, t_data *data)
{
	t_texture	*new_buf;
	t_texture	*old_buf;
	int			old_size;

	old_buf = data->sprite_tex_buffer;
	old_size = data->sprite_tex_num * sizeof(t_texture);
	if (!ft_isspace(str[1]) && (str[1] != 'A' || !ft_isspace(str[2])))
		ft_cub_error();
	data->sprite_tex_num += 1;
	new_buf = (t_texture*)malloc(sizeof(t_texture));
	if (!new_buf)
		ft_memory_error();
	if (old_buf)
	{
		free(new_buf);
		new_buf = ft_realloc(old_buf, old_size, old_size + sizeof(t_texture));
	}
	data->sprite_tex_buffer = new_buf;
	if (str[1] != 'A')
		ft_set_sprite_tex_data(str, data, &new_buf[data->sprite_tex_num - 1]);
	else
		ft_set_animation_data(str, data, &new_buf[data->sprite_tex_num - 1]);
	return (0);
}
