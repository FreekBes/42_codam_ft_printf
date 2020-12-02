/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_output.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 20:54:27 by fbes          #+#    #+#                 */
/*   Updated: 2020/12/02 20:16:32 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	write_empty(int length)
{
	if (length > 0)
	{
		write(1, " ", 1);
		write_empty(length - 1);
	}
}

static int	get_written_len(t_conv *conv, void *input)
{
	if (conv->type == 's')
		return ((int)ft_strlen(input));
	else if (conv->type == 'c' || conv->type == '%')
		return (1);
	else if (conv->type == 'd' || conv->type == 'i')
		return (ft_isneg((int)input) + ft_numlen(ft_abs((int)input), 10));
	else if (conv->type == 'u')
		return (ft_numlen((unsigned int)input, 10));
	else if (conv->type == 'X' || conv->type == 'x')
		return (-ft_isneg((int)input) + ft_numlen((unsigned int)input, 16));
	else if (conv->type == 'p')
		return (ft_ptrlen((intptr_t)input));
	return (0);
}

static int	write_output(t_conv *conv, void *input, int written_len)
{
	if (conv->type == 's')
		write(1, input, (conv->precision > -1 ? conv->precision : written_len));
	else if (conv->type == 'c')
		written_len = ft_putchar_fd((char)input, 1);
	else if (conv->type == 'd' || conv->type == 'i')
		written_len = ft_putnbr_fd((int)input, 1);
	else if (conv->type == 'u')
		written_len = ft_putnbr_base_fd((unsigned int)input, "0123456789", 1);
	else if (conv->type == 'X')
		written_len = ft_putnbr_base_fd((int)input, "0123456789ABCDEF", 1);
	else if (conv->type == 'x')
		written_len = ft_putnbr_base_fd((int)input, "0123456789abcdef", 1);
	else if (conv->type == 'p')
		written_len = ft_putptr_fd((intptr_t)input, 1);
	else if (conv->type == '%')
		written_len = ft_putchar_fd('%', 1);
	else
		written_len = 0;
	return (written_len);
}

void		handle_conv(t_conv *conv, void *input)
{
	int		written_len;

	written_len = get_written_len(conv, input);
	if (written_len < conv->width)
		write_empty(conv->width - written_len);
	written_len = write_output(conv, input, written_len);
	if (conv->width < 0 && -written_len > conv->width)
		write_empty(-(conv->width) - written_len);
}
