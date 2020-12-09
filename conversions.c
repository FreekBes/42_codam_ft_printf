/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 18:38:35 by fbes          #+#    #+#                 */
/*   Updated: 2020/12/09 19:43:49 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** new_conv creates and returns a new conversion structure, with
** the type set as char c. the length of the whole conversion
** is defined in parameter format_size. this length is then used
** while writing non-conversions in the format string to the output.
** please note that the conversion type can be invalid (not in
** VALID_CONVERSIONS) - the structure will then still be created,
** in order to allow for any field width given to be written to output.
*/

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
		conv->empty = ' ';
		conv->alignment = 1;
	}
	return (conv);
}

/*
** del_conv is used for the ft_lstclear function in case of errors.
*/

static void		del_conv(void *conv)
{
	free(conv);
}

/*
** parse_conv_simple parses a format string in a simple manner.
** it can only handle format strings without any flag fields.
** flag fields are set in VALID_FIELDS.
*/

static int		parse_conv_simple(t_list **convs, const char **s)
{
	t_conv		*conv;

	conv = new_conv(*s, *((*s) + 1), 2);
	if (conv)
		ft_lstadd_back(convs, ft_lstnew(conv));
	else
	{
		ft_lstclear(convs, &del_conv);
		return (0);
	}
	(*s)++;
	return (1);
}

/*
** parse_conv_complex parses a format string in a more complex manner.
** it will first loop through the format string until it finds a character
** NOT in VALID_FIELDS, which will then be set as the conversion type.
** a character pointer c is set for field flag checks. first it will check
** if the 0 flag is present. if so, the empty character for this conversion will
** be set to 0 (instead of the default space). then, it will check if a field width
** if a precision has been given, by chcking if *c == '.'. if so, the precision
** will be set to that number and the pointer c will get increased by the amount
** of digits in that precision field, in order to check for a
*/

static int		parse_conv_complex(t_list **convs, const char **s)
{
	const char	*type;
	t_conv		*conv;
	const char	*c;

	c = *s + 1;
	type = c;
	while (ft_strchr(VALID_FIELDS_INCL_DIGITS, (int)*type))
		type++;
	conv = new_conv(*s, (char)*type, type - *s + 1);
	if (conv)
	{
		while (ft_strchr(VALID_FIELDS, (int)*c))
		{
			if (*c == '0')
				conv->empty = '0';
			else if (*c == '-')
				conv->alignment = -1;
			c++;
		}
		if (ft_isdigit((int)*c))
		{
			conv->width = ft_atoi(c);
			c += ft_numlen(conv->precision, 10);
		}
		else if (*c == '*')
		{
			conv->width = 0;
			c++;
		}
		if (*c == '.')
		{
			c++;
			if (*c == '*')
				conv->precision = 0;
			else
				conv->precision = ft_atoi(c);
		}
		ft_lstadd_back(convs, ft_lstnew(conv));
	}
	else
	{
		ft_lstclear(convs, &del_conv);
		return (0);
	}
	*s = type;
	return (1);
}

t_list			*parse_convs(const char *s)
{
	t_list		*convs;
	t_conv		*last;

	convs = NULL;
	while (*s)
	{
		if (*s == '%' && ft_strchr(VALID_CONVERSIONS, (int)*(s + 1)))
		{
			if (!parse_conv_simple(&convs, &s))
				return (NULL);
		}
		else if (*s == '%' && ft_strchr(VALID_FIELDS_INCL_DIGITS, (int)*(s + 1)))
		{
			if (!parse_conv_complex(&convs, &s))
				return (NULL);
		}
		s++;
	}
	last = new_conv(s, '\0', 0);
	ft_lstadd_back(&convs, ft_lstnew(last));
	return (convs);
}
