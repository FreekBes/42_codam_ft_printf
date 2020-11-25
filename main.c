/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 17:51:53 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/25 20:12:04 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	ft_printf("ft_printf: %8s, %s, %d, %c, %i, %%%%, hoi\n", "test", "boe", 42, 'b', -64);
	printf("   printf: %8s, %s, %d, %c, %i, %%%%, hoi\n", "test", "boe", 42, 'b', -64);
	return (0);
}
