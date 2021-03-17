/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 22:10:16 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/17 18:24:31 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
handle_convs handles all conversions in the linked list *conversions
and returns the amount of characters printed, or -1 on error.

It loops through the linked list, until either conv_li == NULL or
the conversion type is '\0', printing all characters in the format
string in between the conversions in the linked list, then writing the
conversions themselves, while keeping track of the amount of characters
printed. The pointer *start keeps track of the start of the in-betweens.
After the loop, the remaining characters in the format string get printed.
*/

static int	handle_convs(const char *start, t_list *conversions)
{
	int			temp_res;
	int			chars_printed;
	t_list		*conv_li;

	conv_li = conversions;
	chars_printed = 0;
	while (conv_li && ((t_conv *)conv_li->content)->type != '\0')
	{
		chars_printed += ((t_conv *)conv_li->content)->position - start;
		write(1, start, ((t_conv *)conv_li->content)->position - start);
		temp_res = write_conv((t_conv *)conv_li->content);
		if (temp_res < 0)
			return (-1);
		chars_printed += temp_res;
		start = ((t_conv *)conv_li->content)->end;
		conv_li = conv_li->next;
	}
	chars_printed += ft_putstr_fd((char *)start, 1);
	ft_lstclear(&conversions, &del_conv);
	return (chars_printed);
}

int	ft_printf(const char *format, ...)
{
	va_list	params;
	t_list	*conversions;

	va_start(params, format);
	conversions = parse_convs(&params, format);
	va_end(params);
	if (!conversions)
		return (-1);
	return (handle_convs(format, conversions));
}
