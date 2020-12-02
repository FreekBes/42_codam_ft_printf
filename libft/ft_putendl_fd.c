/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 21:51:22 by fbes          #+#    #+#                 */
/*   Updated: 2020/12/02 19:13:48 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putendl_fd(char *s, int fd)
{
	int	written_chars;

	written_chars = ft_putstr_fd(s, fd);
	written_chars += ft_putchar_fd('\n', fd);
	return (written_chars);
}
