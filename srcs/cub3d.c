/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:02:32 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/04 18:51:45 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char **argv)
{
	t_data		data;
	t_player	*p;

	data.n = 0;
	data.s = 0;
	data.e = 0;
	data.w = 0;
	data.screenshot = 0;
	if (argc < 2 || argc > 3)
		ft_arg_error();
	else if (argc == 3)
		data.screenshot = !ft_strcmp(argv[2], "--save") ? 1 : ft_arg_error();
	ft_init_data(&data, argv[1], 0.05, 0.15);
	p = data.player;
	ft_init_soldier(&data);
	ft_render(&data, data.mlx, data.player, data.map);
	ft_loop(&data);
	return (0);
}
