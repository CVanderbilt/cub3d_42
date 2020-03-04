/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:21:19 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/04 14:36:04 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_linit(int *l1, int *l2)
{
	*l1 = 0;
	*l2 = 0;
}

static void	ft_jinit(int *j, int *i)
{
	*j = -1;
	*i = -1;
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		l[2];
	int		i;
	int		j;
	char	*ret;

	ft_linit(&l[0], &l[1]);
	if (!s1 || !s2)
		return (0);
	while (s1[l[0]] || s2[l[1]])
	{
		l[0] = s1[l[0]] ? l[0] + 1 : l[0];
		l[1] = s2[l[1]] ? l[1] + 1 : l[1];
	}
	if (!(ret = malloc((l[0] + l[1] + 1) * sizeof(char))))
		return (0);
	ft_jinit(&j, &i);
	while (s1[++i])
		ret[i] = s1[i];
	while (s2[++j])
	{
		ret[i] = s2[j];
		i++;
	}
	ret[i] = 0;
	return (ret);
}
