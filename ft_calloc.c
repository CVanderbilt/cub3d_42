/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:51:18 by eherrero          #+#    #+#             */
/*   Updated: 2020/02/25 12:21:52 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void		ft_kk(void *s, size_t n)
{
	char *i;

	i = (char*)s;
	while (n > 0)
	{
		*(i++) = 0;
		n--;
	}
}

void			*ft_calloc(size_t count, size_t size)
{
	void *p;

	if (!(p = malloc(count * size)))
		return (0);
	ft_kk(p, count * size);
	return (p);
}
