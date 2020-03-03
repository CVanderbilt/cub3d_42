/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:50:29 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/03 15:01:10 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_memory_error(void)
{
	write(1, "memory error\n", 13);
	exit(EXIT_FAILURE);
	return (0);
}

int				ft_map_error(void)
{
	write(1, "map error\n", 10);
	exit(EXIT_FAILURE);
	return (0);
}

int				ft_cub_error(void)
{
	write(1, "cub error\n", 10);
	exit(EXIT_FAILURE);
	return (0);
}

int				ft_arg_error(void)
{
	write(1, "argument error\n", 15);
	exit(EXIT_FAILURE);
	return (0);
}

int				ft_other_error(char *str, char *str2)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	while (str2[j])
		j++;
	write(1, str, i);
	write(1, ":", 1);
	write(1, str2, j);
	exit(EXIT_FAILURE);
	return (0);
}
