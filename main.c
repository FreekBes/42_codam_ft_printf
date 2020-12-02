/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 17:51:53 by fbes          #+#    #+#                 */
/*   Updated: 2020/12/02 19:46:27 by fbes          ########   odam.nl         */
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
	ft_printf("ft_printf: %8s, %8s, %8d, %8c, %8i, %%%%, hoi\n", "test", "boe", 42, 'b', -64);
	printf("   printf: %8s, %8s, %8d, %8c, %8i, %%%%, hoi\n", "test", "boe", 42, 'b', -64);
	ft_printf("ft_printf: %16X, %16d, %16p, %16x, %16u, jaja\n", 42, 0, pointer, -419857856, 4294967295);
	printf("   printf: %16X, %16d, %16p, %16x, %16u, jaja\n", 42, 0, pointer, -419857856, 4294967295);
	return (0);
}
