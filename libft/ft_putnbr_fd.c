/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/12 18:42:02 by fbes          #+#    #+#                 */
/*   Updated: 2020/12/02 19:05:03 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_putnbr_fd(int n, int fd)
{
	unsigned int	written_chars;

	written_chars = 0;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		written_chars++;
		n *= -1;
	}
	return (written_chars + ft_putnbr_base_fd((unsigned int)n, "0123456789", fd));
}
