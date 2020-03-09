/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pickup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:53:01 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/09 14:53:28 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_pickup(t_data *data)
{
	int			i;
	t_sprite	*t;

	i = -1;
	t = data->sprite_buffer;
	while (++i < data->sprites_num)
		if (t[i].type == 2)
			if ((int)data->player->x == (int)t[i].x &&
					(int)data->player->y == (int)t[i].y)
			{
				if (data->player->health < 100)
				{
					data->player->health += 25;
					data->player->health = data->player->health > 100 ?
						100 : data->player->health;
					system("afplay ./assets/sounds/Health.wav &");
					t[i].type = 3;
				}
			}
}
