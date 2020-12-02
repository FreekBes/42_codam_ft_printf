/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putptr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 18:37:56 by fbes          #+#    #+#                 */
/*   Updated: 2020/12/02 18:41:32 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		nbr_loop(intptr_t ptr, int fd)
{
	static char base[] = "0123456789abcdef";

	if (ptr != 0)
	{
		nbr_loop(ptr / 16, fd);
		write(fd, &base[ptr % 16], 1);
	}
}

void			ft_putptr_fd(intptr_t ptr, int fd)
{
	write(fd, "0x", 2);
	if (ptr == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	nbr_loop(ptr, fd);
}
