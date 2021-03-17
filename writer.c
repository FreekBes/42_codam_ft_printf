/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   writer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 22:44:54 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/17 17:44:09 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
write_empty writes the character c to the output, int length times.
It is not very efficient for larger lenghts (many calls to write).
Might improve that later on by using malloc and ft_memset.
*/

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

/*
input_to_output converts the value where the input pointer points at,
to a string, which gets used later on when writing the conversion to
the output.

In case the conversion is not any of the ones supported, the conversion
type will get converted to a string instead (in order to support %%,
for example).

Before returning, the precision gets handled first - meaning the string
will get truncated, or 0 characters will get prepended, depending on
the conversion type.
*/

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

/*
write_output writes the conversion to the output and returns
the amount of characters written by this method.

For the pointer type, len will get increased by 2, to make up
for the extra "0x" printed before the output.

If the conversion type is of type c (character) and the input
character was a null character, len needs to be increased by 1.

If the prepend character (for the width) is 0, and the first
character on the output is a - character, the - gets printed already.
The prepend character can only be 0 for numeric conversions.

Then, if the output strlen is less than the width set in the conversion,
and the conversion needs to be aligned to the right,
the prepend character gets printed "width - len" times.

Then the output gets printed. In case the prepend character was 0,
the - character gets skipped if it's the first character in output,
since it was printed in an earlier step.

If the conversion type is of type c (character) and the input
character was a null character, a \x00 character gets printed.
The ft_putstr_fd function earlier, would not have written anything
to the output, since it found the null character right away
(strlen was 0 in ft_putstr_fd).

As the last step, if the conversion had to be aligned to the left,
and the output strlen was less than the width set in the conversion,
the prepend character gets printed "width - len" times.
*/

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
