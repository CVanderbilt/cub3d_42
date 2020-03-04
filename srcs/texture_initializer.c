/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_initializer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 16:03:22 by eherrero          #+#    #+#             */
/*   Updated: 2020/03/04 18:41:28 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_init_texture_aux(t_init_texture *p, t_texture *t)
{
	char *line;

	p->e = 1;
	p->fd = open(p->path, O_RDONLY);
	if (get_next_line(p->fd, &line) < 0)
		ft_other_error("error loading texture", p->path);
	free(line);
	get_next_line(p->fd, &line);
	free(line);
	get_next_line(p->fd, &line);
	free(line);
	get_next_line(p->fd, &line);
	p->fd_old = p->fd;
	p->fd = 0;
	while (!ft_isdigit(line[p->fd]))
		p->fd++;
	t->width = ft_atoi(line + p->fd);
	while (ft_isdigit(line[p->fd]))
		p->fd++;
	while (!ft_isdigit(line[p->fd]))
		p->fd++;
	t->height = ft_atoi(line + p->fd);
	return (line);
}

void	ft_init_texture(t_mlx *mlx, t_texture *t, char *path)
{
	char			*line;
	t_init_texture	p;

	p.path = path;
	line = ft_init_texture_aux(&p, t);
	t->bpp = 4;
	t->size_line = t->bpp * t->width;
	p.w = (int)t->width;
	p.h = (int)t->height;
	t->img = mlx_xpm_file_to_image(mlx->ptr, path, &p.w, &p.h);
	t->addr = (int*)mlx_get_data_addr(t->img, &(t->bpp),
			&(t->size_line), &p.e);
	free(line);
	while (get_next_line(p.fd_old, &line) > 0)
		free(line);
	free(line);
	close(p.fd_old);
	t->real_width = t->width;
	t->real_height = t->height;
}
