/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eherrero <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 14:28:45 by eherrero          #+#    #+#             */
/*   Updated: 2020/02/28 15:53:16 by eherrero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		while (*s)
		{
			write(fd, s, 1);
			s++;
		}
}

int	ft_dgts_base(long int n, int base_size)
{
	int div;
	int i;

	if (base_size <= 1)
		return (0);
	div = 1;
	i = 0;
	n = n < 0 ? n * -1 : n;
	if (n < base_size)
		return (1);
	while (n > 0)
	{
		n /= base_size;
		i++;
	}
	return (i);
}
int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int			ft_memory_error(void)
{
	printf("memory_error\n");
	exit(1);
	return (0);
}

char		*ft_itoa_base(long long int n, char *base)
{
	int		len;
	int		min;
	int		dgts;
	char	*nbr_base;

	if (!base)
		return (0);
	len = ft_strlen(base);
	dgts = n >= 0 ? ft_dgts_base(n, len) : ft_dgts_base(n, len) + 1;
	if (!(nbr_base = malloc(dgts + 1)))
		return (0);
	nbr_base[0] = '-';
	nbr_base[dgts] = 0;
	min = n >= 0 ? 0 : 1;
	n *= n >= 0 ? 1 : -1;
	while (--dgts >= min)
	{
		nbr_base[dgts] = base[n % len];
		n /= len;
	}
	return (nbr_base);
}



char	*ft_space_treat(char *str)
{
	int i;
	int	j;
	int pair;
	char *ret;

	i = ft_strlen(str);
	//printf("tamaño %d\n", i);
	ret = (char*)malloc(i + i/2);
	if (!ret)
		ft_memory_error();
	pair = 0;
	j = 0;
	if (i % 2)
	{
	//	printf("entra a if %d\n", i % 2);
		ret[j++] = '0';
		pair = 1;
	}
	//printf("recibe >%s< reserva %d\n", str, i + i/2);
	i = -1;
	while (str[++i])
	{
		if (pair == 2)
		{
			//printf("  escribimos > <\n");
			ret[j++] = ' ';
			pair = 0;
		}
		ret[j++] = str[i];
		//printf("  escribimos >%c<\n", str[i]);
		pair++;
	}
	ret[j] = 0;
	//printf("devuelve >%s<\n", ret);
	free (str);
	return (ret);
}

void	ft_create_bmp_img(int *img, int height, int width)
{
	int		fd;
	int		i;
	char	*str_width;
	char	*str_height;

	fd = open ("save.bmp", O_WRONLY | O_TRUNC | O_CREAT);
	// "42 4D 4C 00 00 00 00 00 00 00 1A 00 00 00 0C 00 00 00"
	write (fd, "42 4D 4C 00 00 00 00 00 00 00 1A 00 00 00 0C 00 00 00", 53);
	str_width = ft_itoa_base(width, "0123456789ABCDEF");
	str_height = ft_itoa_base(height, "0123456789ABCDEF");
	str_width = ft_space_treat(str_width);
	str_height = ft_space_treat(str_height);
	write (fd, " ", 1);
	//printf("imprime %s\n", str_width);
	ft_putstr_fd(str_width, fd);
	write (fd, " ", 1);
	//printf("imprime %s\n", str_height);
	ft_putstr_fd(str_height, fd);
	free(str_width);
	free(str_height);
	i = 
}

int main()
{
	int kk;
	ft_create_bmp_img(&kk, 5000, 10000);
}
