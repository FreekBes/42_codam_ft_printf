/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 17:41:41 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/25 21:02:01 by fbes          ########   odam.nl         */
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
		write(1, "[WARNING] conversions == NULL!!!\n", 33);
	conv_li = conversions;
	start = format;
	while (conv_li)
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
