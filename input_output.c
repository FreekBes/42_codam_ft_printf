/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_output.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 20:54:27 by fbes          #+#    #+#                 */
/*   Updated: 2020/12/02 18:42:24 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_empty(int length)
{
	if (length > 0)
	{
		write(1, " ", 1);
		write_empty(length - 1);
	}
}

void	handle_conv(t_conv *conv, void *input)
{
	int		len;

	if (conv->type == 's')
	{
		len = (int)ft_strlen(input);
		if (len < conv->width)
			write_empty(conv->width - len);
		write(1, input, (conv->precision > -1 ? conv->precision : len));
		if (conv->width < 0 && -len > conv->width)
			write_empty(-(conv->width) - len);
	}
	else if (conv->type == 'c')
		ft_putchar_fd((char)input, 1);
	else if (conv->type == 'd' || conv->type == 'i')
		ft_putnbr_fd((int)input, 1);
	else if (conv->type == 'X')
		ft_putnbr_base_fd((int) input, "0123456789ABCDEF", 1);
	else if (conv->type == 'x')
		ft_putnbr_base_fd((int) input, "0123456789abcdef", 1);
	else if (conv->type == 'p')
		ft_putptr_fd((intptr_t) input, 1);
	else if (conv->type == '%')
		ft_putchar_fd('%', 1);
	else
	{
		ft_putstr_fd("[INVALID_TYPE=", 1);
		ft_putchar_fd(conv->type, 1);
		ft_putchar_fd(']', 1);
	}
}
