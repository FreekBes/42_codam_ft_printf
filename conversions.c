/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 18:38:35 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/25 20:43:34 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_conversion	*new_conversion(const char *pos, char c, int format_size)
{
	t_conversion	*conv;

	conv = malloc(sizeof(t_conversion));
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

static void			del_conversion(void *conv)
{
	free(conv);
}

int					parse_conversion_simple(t_list **conversions, const char **s)
{
	t_conversion	*temp;

	temp = new_conversion(*s, *((*s) + 1), 2);
	if (temp)
		ft_lstadd_back(conversions, ft_lstnew(temp));
	else
	{
		ft_lstclear(conversions, &del_conversion);
		return (0);
	}
	(*s)++;
	return (1);
}

int					parse_conversion_complex(t_list **conversions, const char **s)
{
	const char		*type;
	t_conversion	*temp;

	type = *s + 1;
	while (ft_strchr(VALID_FIELDS, (int)*type))
		type++;
	temp = new_conversion(*s, (char)*type, type - *s + 1);
	if (temp)
	{
		if (*((*s) + 1) == '.')
			temp->precision = ft_atoi(*s + 2);
		else if (ft_strchr("1234567890", *((*s) + 1)))
			temp->width = ft_atoi(*s + 1);
		ft_lstadd_back(conversions, ft_lstnew(temp));
	}
	else
	{
		ft_lstclear(conversions, &del_conversion);
		return (0);
	}
	*s = type;
	return (1);
}

t_list				*parse_conversions(const char *s)
{
	t_list			*conversions;

	conversions = NULL;
	while (*s)
	{
		if (*s == '%' && ft_strchr(VALID_CONVERSIONS, (int) *(s + 1)))
		{
			if (!parse_conversion_simple(&conversions, &s))
				return (NULL);
		}
		else if (*s == '%' && ft_strchr(VALID_FIELDS, (int) *(s + 1)))
		{
			if (!parse_conversion_complex(&conversions, &s))
				return (NULL);
		}
		s++;
	}
	return (conversions);
}
