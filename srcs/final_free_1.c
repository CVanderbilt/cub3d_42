/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_free_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:36:15 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/09 14:43:26 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_sprites(t_data *data)
{
	t_sprite	*s;

	s = data->sprite_buffer;
	free(s);
}

void	ft_free_mlx(t_mlx *mlx)
{
	mlx_destroy_image(mlx->ptr, mlx->screen);
	mlx_destroy_window(mlx->ptr, mlx->window);
}

int		ft_free_and_exit(void *param)
{
	t_data *data;

	data = (t_data*)param;
	ft_free_map(data);
	free(data->buffer_z);
	ft_free_textures(data);
	free(data->sprite_buffer);
	free(data->player);
	ft_free_mlx(data->mlx);
	exit(0);
	return (0);
}
