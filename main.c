/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 17:51:53 by fbes          #+#    #+#                 */
/*   Updated: 2020/12/02 18:42:51 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	int		testing;
	int		*pointer;
	intptr_t test;

	testing = 9999;
	pointer = &testing;
	ft_printf("ft_printf: %-8s, %s, %d, %c, %i, %%%%, hoi\n", "test", "boe", 42, 'b', -64);
	printf("   printf: %-8s, %s, %d, %c, %i, %%%%, hoi\n", "test", "boe", 42, 'b', -64);
	ft_printf("ft_printf: %X, %d, %p, %x\n", 42, 0, pointer, -419857856);
	printf("   printf: %X, %d, %p, %x\n", 42, 0, pointer, -419857856);
	return (0);
}
