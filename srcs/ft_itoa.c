/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:09:35 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/04 14:27:26 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_dgts(long int n)
{
	int div;
	int i;

	div = 1;
	i = 0;
	n = n < 0 ? n * -1 : n;
	if (n < 10)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int			dgts;
	int			min;
	long int	n2;
	char		*p;

	dgts = n >= 0 ? ft_dgts(n) : ft_dgts(n) + 1;
	if (!(p = malloc(dgts + 1)))
		return (0);
	min = n >= 0 ? 0 : 1;
	p[0] = '-';
	p[dgts] = 0;
	n2 = n;
	n2 *= n >= 0 ? 1 : -1;
	while (--dgts >= min)
	{
		p[dgts] = n2 % 10 + 48;
		n2 /= 10;
	}
	return (p);
}
