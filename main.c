/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 17:51:53 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/25 19:53:51 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int		main(int argc, char **argv)
{
	ft_printf("test1234: %.3s, %d, %c, %i, %%%%, hoi\n", "dit is een test", 42, 'b', -64);
	printf("test1234: %.3s, %d, %c, %i, %%%%, hoi\n", "dit is een test", 42, 'b', -64);
	return (0);
}
