/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:50:29 by eherrero          #+#    #+#             */
/*   Updated: 2020/02/25 11:50:52 by eherrero         ###   ########.fr       */
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
