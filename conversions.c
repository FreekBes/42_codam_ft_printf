/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 22:15:37 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/17 15:24:43 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_conv	*new_conv(const char *pos, char c, int format_size)
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

static int	parse_conv(va_list *params, t_list **convs, const char **s)
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
		while (ft_strchr(VALID_FIELDS, (int)*c))
		{
			if (*c == '-')
				conv->alignment = -1;
			else if (*c == '0' && (ft_strchr("diuxX", *type)
					|| conv->alignment > 0))
				conv->prepend = '0';
			c++;
		}
		if (*c == '*')
		{
			conv->width = va_arg(*params, int);
			if (conv->width < 0)
			{
				conv->alignment = -1;
				conv->width *= -1;
				conv->prepend = ' ';
			}
			c++;
		}
		else if (ft_isdigit((int)*c))
		{
			conv->width = ft_atoi(c);
			c += ft_numlen(conv->width, 10);
		}
		if (*c == '.')
		{
			c++;
			if (*c == '*')
				conv->precision = va_arg(*params, int);
			else
				conv->precision = ft_atoi(c);
			conv->prepend = ' ';
		}
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
