/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 17:51:53 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/03 19:41:03 by fbes          ########   odam.nl         */
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
	//ret = printf("   printf: \"%.6i\"\n", -3);
	ret = printf("%.6i\n", -3);
	//ft_ret = ft_printf("ft_printf: \"%.6i\"\n", -3);
	ft_ret = ft_printf("%.6i\n", -3);
	//ret = printf("   printf: %s, %-11srew, %11rew\n", "test123", "test");
	//ft_ret = ft_printf("ft_printf: %s, %-11srew, %11rew\n", "test123", "test");
	printf("   ret: %d\n", ret);
	printf("ft_ret: %d\n", ft_ret);
	return (0);
}
