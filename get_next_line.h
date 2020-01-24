/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 15:28:25 by eherrero          #+#    #+#             */
/*   Updated: 2020/01/16 11:41:33 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 32
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct		s_list
{
	int				fd;
	int				open;
	char			*str;
	struct s_list	*next;
}					t_list;
t_list				*ft_get_list(t_list **head, int fd);
int					get_next_line(int fd, char **line);
int					get_next_line_rec(int fd, char **line);
int					ft_get_pos(char *str, char *set);
int					ft_aux(char **line, t_list *tmp, int pos);
int					ft_supr_lst(t_list **head, t_list *to_del);
char				*ft_strdup(char *str);
char				*ft_strndup(char *str, int n);
char				*ft_strjoin_free(char *str1, char *str2, char c);
char				*ft_strjoin_free_aux(char *str1, char *str2, char c);
#endif
