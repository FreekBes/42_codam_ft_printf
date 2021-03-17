/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   writer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 22:44:54 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/17 16:14:26 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	if (conv->type == 's')
		conv->output = ft_strdup((char *)conv->input);
	else if (conv->type == 'd' || conv->type == 'i')
		conv->output = ft_itoa((int)conv->input);
	else if (conv->type == 'u')
		conv->output = ft_itoa_base((unsigned int)conv->input, DECIMAL);
	else if (conv->type == 'X')
		conv->output = ft_itoa_base((unsigned int)conv->input, HEX_UP);
	else if (conv->type == 'x')
		conv->output = ft_itoa_base((unsigned int)conv->input, HEX_DOWN);
	else if (conv->type == 'p')
		conv->output = ft_ptoa((intptr_t)conv->input);
	else
	{
		conv->output = ft_calloc(2, sizeof(char));
		if (!conv->output)
			return (-1);
		if (conv->type != 'c')
			conv->output[0] = conv->type;
		else
			conv->output[0] = (char)conv->input;
	}
	if (!conv->output)
		return (-1);
	return (handle_precision(conv));
}

static int	write_output(t_conv *conv)
{
	int	len;
	int	ret;

	ret = 0;
	len = ft_strlen(conv->output);
	if (conv->type == 'p')
		len += 2;
	if (conv->type == 'c' && (int)conv->input == '\0')
		len += 1;
	if (conv->prepend == '0' && conv->output[0] == '-')
		ret += ft_putchar_fd('-', 1);
	if (conv->alignment > 0 && len < conv->width)
		ret += write_empty(conv->prepend, conv->width - len);
	if (conv->type == 'p')
		ret += ft_putstr_fd("0x", 1);
	if (conv->prepend == '0' && conv->output[0] == '-')
		ret += ft_putstr_fd(conv->output + 1, 1);
	else
		ret += ft_putstr_fd(conv->output, 1);
	if (conv->type == 'c' && (int)conv->input == '\0')
		ret += ft_putchar_fd('\x00', 1);
	if (conv->alignment < 0 && len < conv->width)
		ret += write_empty(conv->prepend, conv->width - len);
	return (ret);
}

int	write_conv(t_conv *conv)
{
	if (input_to_output(conv))
		return (write_output(conv));
	return (-1);
}
