/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:05:58 by eherrero          #+#    #+#             */
/*   Updated: 2019/12/16 15:06:56 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_free(char *str1, char *str2, char c)
{
	if (!str1)
	{
		if (!(str1 = ft_strdup("")))
			return (0);
		if (c == 'R')
			c = 'B';
		else if (c != 'B')
			c = 'L';
	}
	if (!str2)
	{
		if (!(str2 = ft_strdup("")))
			return (0);
		if (c == 'B' || c == 'L')
			c = 'B';
		else
			c = 'R';
	}
	return (ft_strjoin_free_aux(str1, str2, c));
}

char	*ft_strjoin_free_aux(char *str1, char *str2, char c)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (str1[i])
		i++;
	while (str2[j])
		j++;
	if (!(ret = malloc(i + j + 1)))
		return (0);
	i = -1;
	j = -1;
	while (str1[++i])
		ret[i] = str1[i];
	while (str2[++j])
		ret[i + j] = str2[j];
	ret[i + j] = 0;
	if (c == 'L' || c == 'B')
		free(str1);
	if (c == 'R' || c == 'B')
		free(str2);
	return (ret);
}

char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i])
		i++;
	i = i > n ? i : n;
	if (!(ret = malloc(i + 1)))
		return (0);
	i = 0;
	while (str[i] && i < n)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char	*ft_strdup(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (ft_strndup(str, i));
}

int		ft_get_pos(char *str, char *set)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if (!str || !set)
		return (-1);
	while (str[++i])
	{
		while (set[++j])
			if (set[j] == str[i])
				return (i);
		j = -1;
	}
	return (-1);
}
