/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 14:41:46 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/05 14:44:06 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_open_check(char *map, int flags)
{
	int fd;

	if (!map)
		ft_other_error("null map", "null map");
	fd = open(map, flags);
	if (fd < 0)
		ft_other_error("problem opening map", map);
	return (fd);
}
