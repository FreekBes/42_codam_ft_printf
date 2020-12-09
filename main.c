/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 17:51:53 by fbes          #+#    #+#                 */
/*   Updated: 2020/12/09 19:43:29 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	int		testing;
	int		*pointer;
	intptr_t test;
	int		ret;
	int		ft_ret;

	testing = 9999;
	pointer = &testing;
	//ret = printf("   printf: %s\n", "test");
	//ft_ret = ft_printf("ft_printf: %s\n", "test");
	ret = printf("   printf: %s, %11srew, %11rew\n", "test123", "test");
	ft_ret = ft_printf("ft_printf: %s, %11srew, %11rew\n", "test123", "test");
	printf("   ret: %d\n", ret);
	printf("ft_ret: %d\n", ft_ret);
	return (0);
}
