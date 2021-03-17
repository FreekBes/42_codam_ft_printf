/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/17 16:03:49 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/17 17:26:26 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
parse_conv_width parses the width, alignment and the prepending character
in the format string, for use in conversion (t_conv) conv.

It first loops through the valid fields (stored in the macro VALID_FIELDS),
checking if a - or 0 character is present. If it is, it will act accordingly.

Then it checks if the next character is an asterisk, if it is,
the width is stored in the va_list, so it fetches it from there.
If not, it will check if the character it's looking at is a digit, and if
it is, it will parse the number from that character onwards and use that
as the new width for the conversion.
*/

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

/*
parse_conv_prec parses the precision field in the format string.

It checks if the . character is present, if it is, it will then check
if the next character is an asterisk (meaning that the precision is stored
in the va_list). If it is not an asterisk, it is assumed to be a number,
which gets parsed with ft_atoi. If no numeric character is present, ft_atoi
will simply return a 0, so that exception is handled as well.
*/

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

/*
parse_conv parses the conversion from the format string.

First it will loop through the format string (starting at *s + 1)
until the current character is no longer one of VALID_FIELDS_DIG and also
not null. The character that is found afterwards, is the conversion type.
Whether or not it is a valid one does not matter, as an invalid conversion
type will later on simply get ignored (the type itself will get printed as
a character instead, meaning %% is handled too). A new conversion will
get created and then parsed further.

First the width is parsed, then the precision, then it checks if the
conversion type is valid. If it is, the input pointer will get set to the
next argument in the va_list.

If the conversion is of the type s (string), and the input is a NULL pointer,
the pointer will get updated, then pointing to the static variable empty,
which contains the string "(null)" for printing.

Once the parsing is complete, the conversion will get added to the back of
the list of conversions (t_list **convs). On success, it will return 1.
*/

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
