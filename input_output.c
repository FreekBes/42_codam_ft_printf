/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_output.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 22:44:54 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/10 23:50:35 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	debug_print_conv(t_conv *conv)
{
	ft_putstr_fd("\n\nCONVERSION STRUCT DEBUGGING CONTENTS\ninput:", 1);
	ft_putptr_fd((intptr_t)conv->input, 1);
	ft_putstr_fd("\nposition: ", 1);
	ft_putptr_fd((intptr_t)conv->position, 1);
	ft_putstr_fd("\nend: ", 1);
	ft_putptr_fd((intptr_t)conv->end, 1);
	ft_putstr_fd("\nwidth: ", 1);
	ft_putnbr_fd(conv->width, 1);
	ft_putstr_fd("\nprecision: ", 1);
	ft_putnbr_fd(conv->precision, 1);
	ft_putstr_fd("\nprepend: ", 1);
	ft_putchar_fd(conv->prepend, 1);
	ft_putstr_fd("\nalignment: ", 1);
	ft_putnbr_fd(conv->alignment, 1);
	ft_putstr_fd("\ntype: ", 1);
	ft_putchar_fd(conv->type, 1);
	ft_putstr_fd("\noutput: \"", 1);
	ft_putstr_fd(conv->output, 1);
	ft_putstr_fd("\"\n\n\n", 1);
}

static int	write_empty(char c, int length)
{
	int	i;

	i = length;
	while (i > 0)
	{
		write(1, &c, 1);
		i--;
	}
	return (length);
}

static int	input_to_output(t_conv *conv)
{
	char	*temp;
	int		len;

	if (conv->type == 's')
		conv->output = ft_strdup((char *)conv->input);
	else if (conv->type == 'd' || conv->type == 'i')
		conv->output = ft_itoa((int)conv->input);
	else
	{
		conv->output = ft_calloc(2, sizeof(char));
		if (!conv->output)
			return (-1);
		conv->output[0] = conv->type;
	}
	if (!conv->output)
		return (-1);
	if (conv->precision > 0)
	{
		len = ft_strlen(conv->output);
		if (len > conv->precision)
		{
			temp = ft_substr(conv->output, 0, conv->precision);
			if (!temp)
				return (-1);
			free(conv->output);
			conv->output = temp;
		}
		else
		{
			temp = ft_calloc(conv->precision + 1, sizeof(char));
			if (!temp)
				return (-1);
			ft_memset(temp, '0', conv->precision - len);
			ft_strlcpy(temp + conv->precision - len, conv->output, len + 1);
			free(conv->output);
			conv->output = temp;
		}
	}
	return (1);
}

static int	write_output(t_conv *conv)
{
	int	len;
	int	ret;

	ret = 0;
	len = ft_strlen(conv->output);
	if (conv->alignment > 0 && len < conv->width)
		ret += write_empty(conv->prepend, conv->width - len);
	ret += ft_putstr_fd(conv->output, 1);
	if (conv->alignment < 0 && len < conv->width)
		ret += write_empty(conv->prepend, conv->width - len);
	return (ret);
}

int	handle_conv(t_conv *conv)
{
	if (input_to_output(conv))
	{
		//debug_print_conv(conv);
		return (write_output(conv));
	}
	return (-1);
}
