/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_extension.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 14:10:52 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/05 14:36:01 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_check_extension(char *str, char *ext)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!str || !ext)
		return (0);
	while (str[i])
		i++;
	while (ext[j])
		j++;
	i--;
	while (--j)
	{
		if (i < 0)
			return (0);
		if (ext[j] != str[i])
			return (0);
		i--;
	}
	return (1);
}
