/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:28:45 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/03 16:25:22 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		int_to_char(unsigned char *c, int i)
{
	c[0] = (unsigned char)(i);
	c[1] = (unsigned char)(i >> 8);
	c[2] = (unsigned char)(i >> 16);
	c[3] = (unsigned char)(i >> 24);
}

static int		bmp_header(int fd, int h, int w, int padsize)
{
	unsigned char	header[54];
	int				filesize;
	int				i;

	filesize = 54 + (w * 3 * h) + (padsize * h);
	i = -1;
	while (++i < 54)
		header[i] = 0;
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	int_to_char(header + 2, filesize);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	int_to_char(header + 18, w);
	int_to_char(header + 22, h);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	return (!(write(fd, header, 54) < 0));
}

static int		bmp_data(int fd, t_data *data, int padsize)
{
	unsigned char	zero[3];
	int				x;
	int				y;
	int				pixel;
	int				*img;

	img = (int*)data->mlx->screen_data;
	y = data->mlx->y;
	zero[0] = 0;
	zero[1] = 0;
	zero[2] = 0;
	while (--y >= 0)
	{
		x = 0;
		while (x < data->mlx->x)
		{
			pixel = img[x + y * data->mlx->x];
			if (write(fd, &pixel, 3) < 0)
				return (0);
			if (padsize > 0 && write(fd, &zero, padsize) < 0)
				return (0);
			x++;
		}
	}
	return (1);
}

int				take_screenshot(t_data *data)
{
	int padsize;
	int fd;

	padsize = (4 - ((int)data->mlx->x * 3) % 4) % 4;
	if ((fd = open("screenshot.bmp", O_WRONLY |
	O_CREAT, 0777 | O_TRUNC | O_APPEND)) < 0)
		return (0);
	bmp_header(fd, data->mlx->y, data->mlx->x, padsize);
	bmp_data(fd, data, padsize);
	close(fd);
	ft_free_and_exit(data);
	return (1);
}
