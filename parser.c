/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/17 16:03:49 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/17 16:05:00 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	parse_conv_width(va_list **params, t_conv **conv, const char **c)
{
	while (ft_strchr(VALID_FIELDS, (int)**c))
	{
		if (**c == '-')
			(*conv)->alignment = -1;
		else if (**c == '0' && (ft_strchr("diuxX", (*conv)->type)
				|| (*conv)->alignment > 0))
			(*conv)->prepend = '0';
		(*c)++;
	}
	if (**c == '*')
	{
		(*conv)->width = va_arg(**params, int);
		if ((*conv)->width < 0)
		{
			(*conv)->alignment = -1;
			(*conv)->width *= -1;
			(*conv)->prepend = ' ';
		}
		(*c)++;
	}
	else if (ft_isdigit((int)**c))
	{
		(*conv)->width = ft_atoi(*c);
		*c += ft_numlen((*conv)->width, 10);
	}
}

static void	parse_conv_prec(va_list **params, t_conv **conv, const char **c)
{
	if (**c == '.')
	{
		(*c)++;
		if (**c == '*')
			(*conv)->precision = va_arg(**params, int);
		else
			(*conv)->precision = ft_atoi(*c);
		(*conv)->prepend = ' ';
	}
}

int	parse_conv(va_list *params, t_list **convs, const char **s)
{
	static char	empty[] = "(null)";
	const char	*type;
	t_conv		*conv;
	const char	*c;

	c = *s + 1;
	type = c;
	while (ft_strchr(VALID_FIELDS_DIG, (int)*type) && (int)*type != '\0')
		type++;
	conv = new_conv(*s, (char)*type, type - *s + 1);
	if (conv)
	{
		parse_conv_width(&params, &conv, &c);
		parse_conv_prec(&params, &conv, &c);
		if (ft_strchr(VALID_CONVERSIONS, (int)conv->type))
			conv->input = va_arg(*params, void *);
		if (!conv->input && conv->type == 's')
			conv->input = &empty;
		ft_lstadd_back(convs, ft_lstnew(conv));
		*s = type;
		return (1);
	}
	return (0);
}
