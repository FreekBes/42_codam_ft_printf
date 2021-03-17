/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 17:51:53 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/17 16:14:14 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

/*
static void	debug_print_conv(t_conv *conv)
{
	ft_putstr_fd("\n\nCONVERSION STRUCT DEBUGGING CONTENTS\ninput:", 1);
	ft_putptr_fd((intptr_t)conv->input, 1);
	ft_putstr_fd("\nposition: ", 1);
	ft_putptr_fd((intptr_t)conv->position, 1);
	ft_putstr_fd("\nend: ", 1);
	ft_putptr_fd((intptr_t)conv->end, 1);
	ft_putstr_fd("\nwidth: ", 1);
	ft_putnbr_fd(conv->width, 1);
	ft_putstr_fd("\nprecision: ", 1);
	ft_putnbr_fd(conv->precision, 1);
	ft_putstr_fd("\nprepend: ", 1);
	ft_putchar_fd(conv->prepend, 1);
	ft_putstr_fd("\nalignment: ", 1);
	ft_putnbr_fd(conv->alignment, 1);
	ft_putstr_fd("\ntype: ", 1);
	ft_putchar_fd(conv->type, 1);
	ft_putstr_fd("\noutput: \"", 1);
	if (conv->output)
		ft_putstr_fd(conv->output, 1);
	else
		ft_putstr_fd("NULL", 1);
	ft_putstr_fd("\"\n\n\n", 1);
}
*/

int	main(void)
{
	int		testing;
	int		*pointer;
	int		ret;
	int		ft_ret;
	static char *s_hidden = "hi low\0don't print me lol\0";

	testing = 9999;
	pointer = &testing;
	ret = printf("   printf: \"%5c\"\n", 0);
	ft_ret = ft_printf("ft_printf: \"%5c\"\n", 0);
	//ret = printf("   printf: \"%*.*s, %*.*s\"\n", 5, 5, "a", "b");
	//ft_ret = ft_printf("ft_printf: \"%*.*s, %*.*s\"\n", 5, 5, "a", "b");
	//ret = printf("   printf: \"%i, %-11.6srew, %%, %-3q, %b, %11rew\"\n", -123, "test");
	//ft_ret = ft_printf("ft_printf: \"%i, %-11.6srew, %%, %-3q, %b, %11rew\"\n", -123, "test");
	printf("   ret: %d\n", ret);
	printf("ft_ret: %d\n", ft_ret);
	return (0);
}
