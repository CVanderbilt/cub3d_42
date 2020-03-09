/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_free_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:36:54 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/09 14:41:17 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_map(t_data *data)
{
	int i;

	i = 0;
	while (i < data->map_height)
	{
		free(data->map[i]);
		free(data->collision_map[i]);
		free(data->arrow_map[i]);
		i++;
	}
	free(data->map);
	free(data->collision_map);
	free(data->arrow_map);
}

void	ft_free_texture(t_data *data, t_texture *t)
{
	mlx_destroy_image(data->mlx->ptr, t->img);
}

void	ft_free_textures(t_data *data)
{
	int i;

	free(data->n_texture);
	free(data->s_texture);
	free(data->e_texture);
	free(data->w_texture);
	ft_free_texture(data, data->mlx->n_img);
	ft_free_texture(data, data->mlx->s_img);
	ft_free_texture(data, data->mlx->e_img);
	ft_free_texture(data, data->mlx->w_img);
	ft_free_texture(data, data->mlx->skybox);
	ft_free_texture(data, data->void_sprite);
	free(data->mlx->n_img);
	free(data->mlx->s_img);
	free(data->mlx->e_img);
	free(data->mlx->w_img);
	free(data->mlx->skybox);
	i = -1;
	while (++i < data->sprite_tex_num)
		ft_free_texture(data, &data->sprite_tex_buffer[i]);
	free(data->sprite_tex_buffer);
}
