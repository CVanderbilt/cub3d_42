/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:04:55 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/03 16:05:45 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_weapon(t_data *data)
{
	ft_init_texture(data->mlx, &data->weapon[0], "assets/weapon/pistol_0.xpm");
	ft_init_texture(data->mlx, &data->weapon[1], "assets/weapon/pistol_1.xpm");
	ft_init_texture(data->mlx, &data->weapon[2], "assets/weapon/pistol_2.xpm");
	ft_init_texture(data->mlx, &data->weapon[3], "assets/weapon/pistol_3.xpm");
	ft_init_texture(data->mlx, &data->weapon[4], "assets/weapon/pistol_4.xpm");
}

void	ft_init_textures(t_data *data)
{
	t_mlx	*mlx;

	mlx = data->mlx;
	ft_init_weapon(data);
	mlx->n_img = (t_texture*)malloc(sizeof(t_texture));
	mlx->s_img = (t_texture*)malloc(sizeof(t_texture));
	mlx->w_img = (t_texture*)malloc(sizeof(t_texture));
	mlx->e_img = (t_texture*)malloc(sizeof(t_texture));
	mlx->skybox = (t_texture*)malloc(sizeof(t_texture));
	if (!mlx->n_img || !mlx->s_img || !mlx->e_img || !mlx->w_img
			|| !mlx->skybox)
		ft_memory_error();
	ft_init_texture(mlx, mlx->n_img, data->n_texture);
	ft_init_texture(mlx, mlx->s_img, data->s_texture);
	ft_init_texture(mlx, mlx->e_img, data->e_texture);
	ft_init_texture(mlx, mlx->w_img, data->w_texture);
	ft_init_texture(mlx, mlx->skybox, "assets/textures/skybox.xpm");
}

void	ft_init_extra_animations(t_data *data)
{
	t_texture *t;

	t = (t_texture *)malloc(sizeof(t_texture));
	if (!t)
		ft_memory_error();
	ft_init_texture(data->mlx, t, "assets/soldier_anim/soldier_shoot.xpm");
	t->width = 64;
	data->soldier_shoot = t;
}

void	ft_init_soldier(t_data *data)
{
	t_texture *t;

	ft_init_texture(data->mlx, &data->soldier_anim[0],
			"assets/soldier_anim/soldier_idle.xpm");
	ft_init_texture(data->mlx, &data->soldier_anim[1],
			"assets/soldier_anim/soldier_walk1.xpm");
	ft_init_texture(data->mlx, &data->soldier_anim[2],
			"assets/soldier_anim/soldier_walk2.xpm");
	ft_init_texture(data->mlx, &data->soldier_anim[3],
			"assets/soldier_anim/soldier_walk3.xpm");
	ft_init_texture(data->mlx, &data->soldier_anim[4],
			"assets/soldier_anim/soldier_walk4.xpm");
	t = &(data->soldier_anim[0]);
	t->width = 64;
	t = &(data->soldier_anim[1]);
	t->width = 64;
	t = &(data->soldier_anim[2]);
	t->width = 64;
	t = &(data->soldier_anim[3]);
	t->width = 64;
	t = &(data->soldier_anim[4]);
	t->width = 64;
	ft_init_extra_animations(data);
}
