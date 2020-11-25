/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 18:38:35 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/25 20:04:01 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			get_arg_count(const char *s)
{
	int		count;

	count = 0;
	while (*s)
	{
		if (*s == '%' && ft_strchr(VALID_CONVERSIONS, (int) *(s + 1)))
			count++;
		s++;
	}
	return (count);
}

static t_conversion	*new_conversion(const char *pos, char c, int format_size)
{
	t_conversion	*conv;

	conv = malloc(sizeof(t_conversion));
	if (conv)
	{
		conv->position = pos;
		conv->type = c;
		conv->end = pos + format_size;
	}
	return (conv);
}

static void			del_conversion(void *conv)
{
	free(conv);
}

t_list				*parse_conversions(const char *s)
{
	t_list			*conversions;
	t_conversion	*temp;
	int				arg_count;
	const char		*temp_type;

	conversions = NULL;
	arg_count = get_arg_count(s);
	while (*s)
	{
		if (*s == '%' && ft_strchr(VALID_CONVERSIONS, (int) *(s + 1)))
		{
			temp = new_conversion(s, *(s + 1), 2);
			if (temp)
				ft_lstadd_back(&conversions, ft_lstnew(temp));
			else
			{
				ft_lstclear(&conversions, &del_conversion);
				return (NULL);
			}
			s++;
		}
		else if (*s == '%' && ft_strchr(VALID_FIELDS, (int) *(s + 1)))
		{
			temp_type = s + 1;
			while (ft_strchr(VALID_FIELDS, (int)*temp_type))
				temp_type++;
			temp = new_conversion(s, (char)*temp_type, temp_type - s + 1);
			if (temp)
			{
				if (*(s + 1) == '.')
					temp->precision = ft_atoi(s + 2);
				ft_lstadd_back(&conversions, ft_lstnew(temp));
			}
			else
			{
				ft_lstclear(&conversions, &del_conversion);
				return (NULL);
			}
			s = temp_type;
		}
		s++;
	}
	return (conversions);
}
