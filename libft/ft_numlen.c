/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_numlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/12/02 19:31:44 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/11 02:37:06 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_numlen(unsigned int n, unsigned int base)
{
	if (n < base)
		return (1);
	return (1 + ft_numlen(n / base, base));
}
