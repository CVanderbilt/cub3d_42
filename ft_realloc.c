/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:51:43 by eherrero          #+#    #+#             */
/*   Updated: 2020/02/25 12:22:14 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			*ft_realloc(void *ptr, int prev_size, int new_size)
{
	char	*str;
	char	*ret;
	int		i;

	if (!ptr || prev_size <= 0 || new_size <= 0)
		return (0);
	i = 0;
	str = (char *)ptr;
	ret = ft_calloc(new_size, sizeof(char));
	if (!ret)
		return (0);
	while (i < prev_size)
	{
		ret[i] = str[i];
		i++;
	}
	free(str);
	return ((void *)ret);
}
