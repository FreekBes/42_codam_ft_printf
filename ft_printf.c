/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 17:41:41 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/25 19:13:37 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list			params;
	t_list			*conversions;
	t_list			*conv;

	va_start(params, format);
	conversions = parse_conversions(format);
	conv = conversions;
	while (conv)
	{
		((t_conversion *)conv->content)->input = va_arg(params, void *);
		conv = conv->next;
	}
	conv = conversions;
	while (conv)
	{
		ft_putnbr_fd(((t_conversion *)conv->content)->type, 1);
		ft_putchar_fd(':', 1);
		ft_putstr_fd((char *)((t_conversion *)conv->content)->position, 1);
		ft_putchar_fd(':', 1);
		ft_putendl_fd(((t_conversion *)conv->content)->input, 1);
		conv = conv->next;
	}
	va_end(params);
	return (0);
}
