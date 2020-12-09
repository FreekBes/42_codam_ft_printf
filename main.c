/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 17:51:53 by fbes          #+#    #+#                 */
/*   Updated: 2020/12/09 20:41:01 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		main(void)
{
	int		testing;
	int		*pointer;
	int		ret;
	int		ft_ret;

	testing = 9999;
	pointer = &testing;
	ret = printf("   printf: %.03s\n", NULL);
	ft_ret = ft_printf("ft_printf: %.03s\n", NULL);
	//ret = printf("   printf: %s, %-11srew, %11rew\n", "test123", "test");
	//ft_ret = ft_printf("ft_printf: %s, %-11srew, %11rew\n", "test123", "test");
	printf("   ret: %d\n", ret);
	printf("ft_ret: %d\n", ft_ret);
	return (0);
}
