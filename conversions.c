/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 18:38:35 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/25 20:53:36 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_conv	*new_conv(const char *pos, char c, int format_size)
{
	t_conv		*conv;

	conv = malloc(sizeof(t_conv));
	if (conv)
	{
		conv->position = pos;
		conv->type = c;
		conv->end = pos + format_size;
		conv->precision = -1;
		conv->width = 0;
	}
	return (conv);
}

static void			del_conv(void *conv)
{
	free(conv);
}

static int			parse_conv_simple(t_list **convs, const char **s)
{
	t_conv		*temp;

	temp = new_conv(*s, *((*s) + 1), 2);
	if (temp)
		ft_lstadd_back(convs, ft_lstnew(temp));
	else
	{
		ft_lstclear(convs, &del_conv);
		return (0);
	}
	(*s)++;
	return (1);
}

static int			parse_conv_complex(t_list **convs, const char **s)
{
	const char	*type;
	t_conv		*temp;

	type = *s + 1;
	while (ft_strchr(VALID_FIELDS, (int)*type))
		type++;
	temp = new_conv(*s, (char)*type, type - *s + 1);
	if (temp)
	{
		if (*((*s) + 1) == '.')
			temp->precision = ft_atoi(*s + 2);
		else if (ft_strchr("1234567890", *((*s) + 1)))
			temp->width = ft_atoi(*s + 1);
		ft_lstadd_back(convs, ft_lstnew(temp));
	}
	else
	{
		ft_lstclear(convs, &del_conv);
		return (0);
	}
	*s = type;
	return (1);
}

t_list				*parse_convs(const char *s)
{
	t_list		*convs;

	convs = NULL;
	while (*s)
	{
		if (*s == '%' && ft_strchr(VALID_CONVERSIONS, (int)*(s + 1)))
		{
			if (!parse_conv_simple(&convs, &s))
				return (NULL);
		}
		else if (*s == '%' && ft_strchr(VALID_FIELDS, (int)*(s + 1)))
		{
			if (!parse_conv_complex(&convs, &s))
				return (NULL);
		}
		s++;
	}
	return (convs);
}
