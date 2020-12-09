/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_output.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 20:54:27 by fbes          #+#    #+#                 */
/*   Updated: 2020/12/09 20:40:40 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** write_empty writes length empty characters c to the output.
*/

static int	write_empty(char c, int length)
{
	int i;

	i = length;
	while (i > 0)
	{
		write(1, &c, 1);
		i--;
	}
	return (length);
}

/*
** get_written_len returns the length of the conversion to be written to the output.
** the function returns 1 if the conversion type is invalid,
** since then the conversion type will get printed as a character,
** which is 1 in length.
*/

static int	get_written_len(t_conv *conv, void *input)
{
	int	temp;

	if (conv->type == 's')
	{
		temp = (int)ft_strlen(input);
		if (conv->precision > 0 && conv->precision < temp)
			return (conv->precision);
		return (temp);
	}
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
	return (1);
}

/*
** write_output writes the conversion to the output.
** it takes written_len as a parameter for the length of the conversion's output,
** limiting for example a string conversion to a length of written_len if precision
** is not set. Otherwise precision would be used.
*/

static int	write_output(t_conv *conv, void *input, int written_len)
{
	if (conv->type == 's')
	{
		if (conv->precision > -1 && conv->precision < written_len)
			written_len = conv->precision;
		write(1, input, written_len);
	}
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
		written_len = ft_putchar_fd((char)conv->type, 1);
	return (written_len);
}

/*
** handle_conv handles the conversion. first it retrieves the length to be written
** to output. if that number is smaller than the width given in the format string,
** empty characters will get written to output. then the conversion is written,
** after that empty characters will get written if the width is smaller than 0
** (which states that the conversion should be aligned to the left, thus empty
** characters need to be written to the right side of the conversion).
*/

int			handle_conv(t_conv *conv, void *input)
{
	static char		empty[] = "(null)";
	int				written_len;
	int				ret;

	if (!input)
		input = &empty;
	written_len = get_written_len(conv, input);
	ret = 0;
	if (conv->alignment > 0 &&written_len < conv->width)
		ret += write_empty(conv->prepend, conv->width - written_len);
	ret += write_output(conv, input, written_len);
	if (conv->alignment < 0 && written_len < conv->width)
		ret += write_empty(' ', conv->width - written_len);
	return (ret);
}
