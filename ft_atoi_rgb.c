/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:59:20 by eherrero          #+#    #+#             */
/*   Updated: 2020/02/25 12:00:03 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_atoi_rgb(char *str, int rgb[3])
{
	int	i;

	i = 1;
	if (!ft_isspace(str[1]))
		ft_cub_error();
	while (ft_isspace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		ft_cub_error();
	rgb[0] = ft_atoi(str + i);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ',' && !ft_isdigit(str[i + 1]))
		ft_cub_error();
	rgb[1] = ft_atoi(str + i + 1);
	i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] != ',' && !ft_isdigit(str[i + 1]))
		ft_cub_error();
	rgb[2] = ft_atoi(str + i + 1);
}
