/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/11 00:08:06 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/11 00:22:29 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_valid_base(char *base)
{
	int		i;
	int		j;

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	if (i < 2)
		return (0);
	return (1);
}

static void	nbr_loop(char *ret, unsigned int n, char *base, int base_num)
{
	if (n != 0)
	{
		nbr_loop(ret + 1, n / base_num, base, base_num);
		ret = &base[n % base_num];
	}
}

char	*ft_itoa_base(unsigned int n, char *base)
{
	int		base_num;
	char	*ret;

	base_num = ft_strlen(base);
	if (!is_valid_base(base))
		return (0);
	ret = ft_calloc(ft_numlen(n, base_num) + 1, sizeof(char));
	if (!ret)
		return (NULL);
	if (n == 0)
		ret[0] = base[0];
	nbr_loop(ret, n, base, base_num);
	return (ret);
}
