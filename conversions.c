/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 22:15:37 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/17 16:10:38 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_conv	*new_conv(const char *pos, char c, int format_size)
{
	t_conv	*conv;

	conv = malloc(sizeof(t_conv));
	if (conv)
	{
		conv->position = pos;
		conv->type = c;
		conv->end = pos + format_size;
		conv->precision = -1;
		conv->width = 0;
		conv->prepend = ' ';
		conv->alignment = 1;
		conv->input = NULL;
		conv->output = NULL;
	}
	return (conv);
}

void	del_conv(void *conv)
{
	if (((t_conv *)conv)->output)
		free(((t_conv *)conv)->output);
	free(conv);
}

t_list	*parse_convs(va_list *params, const char *s)
{
	t_list		*convs;
	t_conv		*last;

	convs = NULL;
	while (*s)
	{
		if (*s == '%')
		{
			if (!parse_conv(params, &convs, &s))
			{
				ft_lstclear(&convs, &del_conv);
				return (NULL);
			}
		}
		s++;
	}
	last = new_conv(s, '\0', 0);
	ft_lstadd_back(&convs, ft_lstnew(last));
	return (convs);
}
