/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 11:06:05 by eherrero          #+#    #+#             */
/*   Updated: 2020/01/16 15:20:58 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*ft_get_list(t_list **head, int fd)
{
	t_list *tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	if (!(tmp = malloc(sizeof(t_list))))
		return (0);
	tmp->str = 0;
	tmp->fd = fd;
	tmp->open = 1;
	tmp->next = *head;
	*head = tmp;
	return (tmp);
}

int		ft_aux(char **line, t_list *tmp, int pos)
{
	char *aux;

	if (!(*line = ft_strjoin_free(*line, ft_strndup(tmp->str, pos), 'B')))
		return (0);
	aux = ft_strdup(tmp->str + pos + 1);
	free(tmp->str);
	tmp->str = aux;
	return (1);
}

int		ft_supr_lst(t_list **head, t_list *to_del)
{
	t_list *tmp;

	tmp = *head;
	if (*head == to_del)
	{
		*head = tmp->next;
		free(to_del->str);
		free(to_del);
		return (-1);
	}
	while (tmp)
	{
		if (tmp->next == to_del)
		{
			tmp->next = to_del->next;
			free(to_del->str);
			to_del->str = 0;
			free(to_del);
			to_del = 0;
			return (-1);
		}
		tmp = tmp->next;
	}
	return (-1);
}

int		get_next_line_rec(int fd, char **line)
{
	static t_list	*head;
	t_list			*tmp;
	int				pos;
	char			line_r[BUFFER_SIZE + 1];

	if (!(tmp = ft_get_list(&head, fd)))
		return (-1);
	pos = ft_get_pos(tmp->str, "\n\r");
	if (pos >= 0)
	return (!ft_aux(line, tmp, pos) ? -1 : 1);
	while (tmp->open)
	{
		pos = read(fd, line_r, BUFFER_SIZE);
		if (pos < 0)
			return (ft_supr_lst(&head, tmp));
		line_r[pos] = 0;
		tmp->open = pos;
		tmp->str = ft_strjoin_free(tmp->str, line_r, 'L');
		pos = ft_get_pos(tmp->str, "\n\r");
		if (pos >= 0)
			return (!ft_aux(line, tmp, pos) ? -1 : 1);
	}
	*line = ft_strjoin_free(*line, ft_strdup(tmp->str), 'B');
	ft_supr_lst(&head, tmp);
	return (!*line ? -1 : 0);
}

int		get_next_line(int fd, char **line)
{
	int i;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	*line = 0;
	i = get_next_line_rec(fd, line);
	return (i);
}
