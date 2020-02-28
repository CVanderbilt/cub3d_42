/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:53:29 by eherrero          #+#    #+#             */
/*   Updated: 2020/02/25 11:55:00 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_set_pos(t_player *player, char c, int x, int y)
{
	float	rect;

	rect = 1.57;
	if (player->x != 0 || player->y != 0)
		ft_map_error();
	player->y = (double)x + 0.5;
	player->x = (double)y + 0.5;
	if (c == 'N' || c == 'S')
	{
		player->dir_y = 0;
		player->dir_x = c != 'N' ? 1 : -1;
		player->plane_x = 0;
		player->plane_y = c != 'N' ? 0.66 : -0.66;
	}
	else if (c == 'E' || c == 'W')
	{
		player->dir_x = 0;
		player->dir_y = c == 'E' ? 1 : -1;
		player->plane_y = 0;
		player->plane_x = c == 'E' ? -0.66 : 0.66;
	}
	else
		ft_map_error();
}

int				ft_check_full(char *str, char c)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] != c)
			return (0);
	return (1);
}

int				ft_set_dir_texture(char *str, int i, char **texture)
{
	int		j;
	int		k;
	char	*ret;

	k = 0;
	while (ft_isspace(str[i]))
		i++;
	if (!str[i])
		ft_cub_error();
	j = i;
	while (!ft_isspace(str[i]) && str[i])
		i++;
	ret = (char *)malloc(i - j + 1);
	if (!ret)
	{
		printf("1\n");
		ft_memory_error();
	}
	while (j < i)
		ret[k++] = str[j++];
	ret[k] = 0;
	*texture = ret;
	return (0);
}

char			*ft_get_text(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*ret;

	i = 0;
	if (!ft_isspace(str[i]))
		ft_cub_error();
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (!str[i])
		ft_cub_error();
	j = i;
	while (str[i])
		i++;
	ret = (char*)malloc(i - j + 1);
	if (!ret)
		ft_memory_error();
	k = -1;
	while (++k < i - j)
		ret[k] = str[k + j];
	ret[i - j] = 0;
	return (ret);
}
