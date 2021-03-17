/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 22:10:16 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/17 16:08:16 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list		params;
	t_list		*conversions;
	t_list		*conv_li;
	const char	*start;
	int			ret;

	va_start(params, format);
	conversions = parse_convs(&params, format);
	va_end(params);
	if (!conversions)
		return (-1);
	conv_li = conversions;
	start = format;
	ret = 0;
	while (conv_li && ((t_conv *)conv_li->content)->type != '\0')
	{
		ret += ((t_conv *)conv_li->content)->position - start;
		write(1, start, ((t_conv *)conv_li->content)->position - start);
		ret += write_conv((t_conv *)conv_li->content);
		start = ((t_conv *)conv_li->content)->end;
		conv_li = conv_li->next;
	}
	ret += ft_putstr_fd((char *)start, 1);
	ft_lstclear(&conversions, &del_conv);
	return (ret);
}
