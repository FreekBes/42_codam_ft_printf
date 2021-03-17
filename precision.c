/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   precision.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/17 16:06:16 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/17 17:56:20 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
handle_precision_number adds a certain amount of 0 characters
to the output string by reallocating and moving it, in order to make sure
that the output string is of a certain length (the precision field).
*/

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

/*
handle_precision handles the precision in the input_to_output method.
It returns 1 on success, -1 on failure.

It first checks if the precision actually needs to be handled. If it needs to be,
it will retrieve the len of the output string, and compare that to the required
precision. In case the conversion was of type d or i, the - character gets
excluded from the length.

For strings and numeric conversions with an output starting with '0', the string
gets truncated to the required precision, if it was too long.

For numeric conversions, handle_precision_number gets called, if the length
of the output string was smaller than the required precision.
*/

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
