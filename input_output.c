/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_output.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 20:54:27 by fbes          #+#    #+#                 */
/*   Updated: 2020/12/02 20:05:41 by fbes          ########   odam.nl         */
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
	int		written_len;

	if (conv->type == 's')
		written_len = (int)ft_strlen(input);
	else if (conv->type == 'c' || conv->type == '%')
		written_len = 1;
	else if (conv->type == 'd' || conv->type == 'i')
		written_len = ft_numlen(ft_abs((int)input), 10);
	else if (conv->type == 'u')
		written_len = ft_numlen((unsigned int)input, 10);
	else if (conv->type == 'X' || conv->type == 'x')
		written_len = ft_numlen((unsigned int)input, 16);
	else if (conv->type == 'p')
		written_len = ft_ptrlen((intptr_t)input);
	else
		written_len = 0;
	if (written_len < conv->width)
		write_empty(conv->width - written_len);
	if (conv->type == 's')
		write(1, input, (conv->precision > -1 ? conv->precision : written_len));
	else if (conv->type == 'c')
		ft_putchar_fd((char)input, 1);
	else if (conv->type == 'd' || conv->type == 'i')
		ft_putnbr_fd((int)input, 1);
	else if (conv->type == 'u')
		ft_putnbr_base_fd((unsigned int)input, "0123456789", 1);
	else if (conv->type == 'X')
		ft_putnbr_base_fd((int)input, "0123456789ABCDEF", 1);
	else if (conv->type == 'x')
		ft_putnbr_base_fd((int)input, "0123456789abcdef", 1);
	else if (conv->type == 'p')
		ft_putptr_fd((intptr_t)input, 1);
	else if (conv->type == '%')
		ft_putchar_fd('%', 1);
	else
	{
		written_len = ft_putstr_fd("[INVALID_TYPE=", 1);
		written_len += ft_putchar_fd(conv->type, 1);
		written_len += ft_putchar_fd(']', 1);
	}

	if (conv->width < 0 && -written_len > conv->width)
		write_empty(-(conv->width) - written_len);
}
