/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:57:04 by eherrero          #+#    #+#             */
/*   Updated: 2020/02/28 13:59:58 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_set_animation_data_precheck(char *str, t_texture *t)
{
	int i;

	i = 2;
	if (!ft_isspace(str[i]))
		ft_cub_error();
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		ft_cub_error();
	t->a_directions = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	if (!ft_isspace(str[i]))
		ft_cub_error();
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		ft_cub_error();
	t->a_states = ft_atoi(str + i);
	return (i);
}

void			ft_set_animation_data(char *str, t_data *data, t_texture *t)
{
	int i;

	t->animated = 1;
	i = ft_set_animation_data_precheck(str, t);
	while (ft_isdigit(str[i]))
		i++;
	if (!ft_isspace(str[i]))
		ft_cub_error();
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isalnum(str[i]))
		ft_cub_error();
	ft_init_texture(data->mlx, t, str + i);
	t->width = t->real_width / t->a_directions;
	t->height = t->real_height / t->a_states;
}

void			ft_set_sprite_tex_data(char *str, t_data *data, t_texture *t)
{
	int i;

	i = 1;
	t->a_directions = 1;
	t->a_states = 1;
	t->animated = 0;
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isalnum(str[i]))
		ft_cub_error();
	ft_init_texture(data->mlx, t, str + i);
}
