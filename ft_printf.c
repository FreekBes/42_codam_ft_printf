/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 17:41:41 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/25 19:51:32 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list			params;
	t_list			*conversions;
	t_list			*conv;
	t_conversion	*temp;
	const char		*start;

	va_start(params, format);
	conversions = parse_conversions(format);
	conv = conversions;
	while (conv)
	{
		((t_conversion *)conv->content)->input = va_arg(params, void *);
		conv = conv->next;
	}
	conv = conversions;
	start = format;
	while (conv)
	{
		temp = (t_conversion *)conv->content;
		write(1, start, temp->position - start);
		if (temp->type == 's')
			ft_putstr_fd(temp->input, 1);
		else if (temp->type == 'c')
			ft_putchar_fd((char)temp->input, 1);
		else if (temp->type == 'd' || temp->type == 'i')
			ft_putnbr_fd((int)temp->input, 1);
		else if (temp->type == '%')
			ft_putchar_fd('%', 1);
		else
		{
			ft_putstr_fd("[INVALID_TYPE=", 1);
			ft_putchar_fd(temp->type, 1);
			ft_putchar_fd(']', 1);
		}
		start = temp->end;
		conv = conv->next;
	}
	ft_putstr_fd((char *)start, 1);
	va_end(params);
	return (0);
}
