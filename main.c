/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 17:51:53 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/10 23:56:31 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int	main(void)
{
	int		testing;
	int		*pointer;
	int		ret;
	int		ft_ret;
	static char *s_hidden = "hi low\0don't print me lol\0";

	testing = 9999;
	pointer = &testing;
	ret = printf("   printf: \"%12.7s\"\n", "abcd");
	ft_ret = ft_printf("ft_printf: \"%12.7s\"\n", "abcd");
	//ret = printf("   printf: \"%*.*s, %*.*s\"\n", 5, 5, "a", "b");
	//ft_ret = ft_printf("ft_printf: \"%*.*s, %*.*s\"\n", 5, 5, "a", "b");
	//ret = printf("   printf: \"%i, %-11.6srew, %%, %-3q, %b, %11rew\"\n", -123, "test");
	//ft_ret = ft_printf("ft_printf: \"%i, %-11.6srew, %%, %-3q, %b, %11rew\"\n", -123, "test");
	printf("   ret: %d\n", ret);
	printf("ft_ret: %d\n", ft_ret);
	return (0);
}
