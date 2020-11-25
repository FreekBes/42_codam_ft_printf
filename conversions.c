/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 18:38:35 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/25 19:11:19 by fbes          ########   odam.nl         */
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

static t_conversion	*new_conversion(const char *pos, char c)
{
	t_conversion	*conv;

	conv = malloc(sizeof(t_conversion));
	if (conv)
	{
		conv->position = pos;
		conv->type = c;
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

	conversions = NULL;
	arg_count = get_arg_count(s);
	while (*s)
	{
		if (*s == '%' && ft_strchr(VALID_CONVERSIONS, (int) *(s + 1)))
		{
			temp = new_conversion(s, *(s + 1));
			if (temp)
				ft_lstadd_back(&conversions, ft_lstnew(temp));
			else
			{
				ft_lstclear(&conversions, &del_conversion);
			}
		}
		s++;
	}
	return (conversions);
}
