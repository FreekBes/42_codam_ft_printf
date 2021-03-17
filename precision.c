/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   precision.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/17 16:06:16 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/17 16:10:11 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_precision_number(t_conv **conv, int len)
{
	char	*temp;

	temp = ft_calloc((*conv)->precision + 1, sizeof(char));
	if (!temp)
		return (-1);
	ft_memset(temp, '0', (*conv)->precision);
	if ((*conv)->output[0] == '-')
	{
		temp[0] = '-';
		(*conv)->output[0] = '0';
		ft_strlcpy(temp + (*conv)->precision - len, (*conv)->output, len + 2);
	}
	else
		ft_strlcpy(temp + (*conv)->precision - len, (*conv)->output, len + 1);
	free((*conv)->output);
	(*conv)->output = temp;
	return (1);
}

int	handle_precision(t_conv *conv)
{
	char	*temp;
	int		len;

	if (conv->precision > -1)
	{
		len = ft_strlen(conv->output);
		if ((conv->type == 'd' || conv->type == 'i')
			&& ft_isneg((int)conv->input))
			len--;
		if (len > conv->precision && (conv->type == 's'
				|| (ft_strchr("diuxXp", conv->type) && conv->output[0] == '0')))
		{
			temp = ft_substr(conv->output, 0, conv->precision);
			if (!temp)
				return (-1);
			free(conv->output);
			conv->output = temp;
		}
		else if (len < conv->precision && ft_strchr("diuxXp", conv->type))
			return (handle_precision_number(&conv, len));
	}
	return (1);
}
