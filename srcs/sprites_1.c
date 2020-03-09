/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:55:24 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/09 13:47:29 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_sprite_extra_data_precheck(char *str, t_sprite *s, int i)
{
	while (ft_isdigit(str[i]))
		i++;
	if (!ft_isspace(str[i]))
		ft_cub_error();
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == 'I')
		s->type = 0;
	else
		s->type = str[i] == 'H' ? 1 : 2;
	if (str[i] != 'I' && str[i] != 'H' && str[i] != 'P')
		ft_cub_error();
	if (s->type == 0 || s->type == 2)
		return (-1);
	i++;
	return (i);
}

void			ft_sprite_extra_data(char *str, t_sprite *sprite, int i)
{
	i = ft_sprite_extra_data_precheck(str, sprite, i);
	if (i < 0)
		return ;
	if (!ft_isspace(str[i]))
		ft_cub_error();
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]) && str[i] != '-')
		ft_cub_error();
	sprite->dir_x = ft_atoi(str + i);
	while (ft_isdigit(str[i]) || str[i] == '-')
		i++;
	if (!ft_isspace(str[i]))
		ft_cub_error();
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]) && str[i] != '-')
		ft_cub_error();
	sprite->dir_y = ft_atoi(str + i);
}

int				ft_set_sprite_data_precheck(char *str, t_sprite *sprite)
{
	int i;

	i = 1;
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		ft_cub_error();
	sprite->x = (double)ft_atoi(str + i) + 0.5;
	while (ft_isdigit(str[i]))
		i++;
	if (!ft_isspace(str[i]))
		ft_cub_error();
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		ft_cub_error();
	sprite->y = (double)ft_atoi(str + i) + 0.5;
	while (ft_isdigit(str[i]))
		i++;
	if (!ft_isspace(str[i]))
		ft_cub_error();
	return (i);
}

void			ft_set_sprite_data(char *str, t_sprite *sprite)
{
	int i;

	i = ft_set_sprite_data_precheck(str, sprite);
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		ft_cub_error();
	sprite->texture = ft_atoi(str + i);
	ft_sprite_extra_data(str, sprite, i);
	sprite->comprobador = 15;
	sprite->back_x = sprite->x;
	sprite->back_y = sprite->y;
	sprite->dir_x = 0;
	sprite->dir_y = 1;
	sprite->state = 0;
}

int				ft_set_new_sprite(char *str, t_data *data)
{
	t_sprite	*new_buff;
	char		*old_buff;
	int			i;
	int			end;
	int			old_size;

	i = -1;
	end = sizeof(t_sprite) * data->sprites_num;
	data->sprites_num++;
	new_buff = (t_sprite*)malloc(data->sprites_num * sizeof(t_sprite));
	old_buff = (char*)data->sprite_buffer;
	old_size = sizeof(t_sprite) * (data->sprites_num - 1);
	if (old_buff)
	{
		free(new_buff);
		new_buff = ft_realloc(old_buff, old_size, old_size + sizeof(t_sprite));
	}
	data->sprite_buffer = new_buff;
	ft_set_sprite_data(str, &new_buff[data->sprites_num - 1]);
	return (1);
}
