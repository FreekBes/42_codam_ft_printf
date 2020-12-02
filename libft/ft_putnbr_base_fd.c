/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_base_fd.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 17:49:16 by fbes          #+#    #+#                 */
/*   Updated: 2020/12/02 18:27:40 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_valid_base(char *base)
{
	int i;
	int j;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	if (i < 2)
		return (0);
	return (1);
}

static void		nbr_loop(unsigned int n, char *base, int base_num, int fd)
{
	if (n != 0)
	{
		nbr_loop(n / base_num, base, base_num, fd);
		write(fd, &base[n % base_num], 1);
	}
}

void			ft_putnbr_base_fd(unsigned int n, char *base, int fd)
{
	int		base_num;

	base_num = ft_strlen(base);
	if (!is_valid_base(base))
		return ;
	if (n == 0)
	{
		write(fd, base, 1);
		return ;
	}
	nbr_loop(n, base, base_num, fd);
}
