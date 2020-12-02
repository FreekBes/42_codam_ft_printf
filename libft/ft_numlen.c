/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 19:31:44 by fbes          #+#    #+#                 */
/*   Updated: 2020/12/02 20:01:36 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** Includes the minus character for negative numbers!
*/

int		ft_numlen(unsigned int n, int base)
{
	if (n < 0)
		return (1 + ft_numlen(-n, base));
	if (n < 10)
		return (1);
	return (1 + ft_numlen(n / base, base));
}
