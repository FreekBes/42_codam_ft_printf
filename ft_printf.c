/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 17:41:41 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/25 21:35:04 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list			params;
	t_list			*conversions;
	t_list			*conv_li;
	const char		*start;

	va_start(params, format);
	conversions = parse_convs(format);
	if (!conversions)
		return (-1);
	conv_li = conversions;
	start = format;
	while (conv_li && ((t_conv *)conv_li->content)->type != '\0')
	{
		write(1, start, ((t_conv *)conv_li->content)->position - start);
		handle_conv((t_conv *)conv_li->content, va_arg(params, void *));
		start = ((t_conv *)conv_li->content)->end;
		conv_li = conv_li->next;
	}
	ft_putstr_fd((char *)start, 1);
	va_end(params);
	return (0);
}
