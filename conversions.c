/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   conversions.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 22:15:37 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/17 17:55:38 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
new_conv creates a new conversion structure element, of a certain
type (char c). It also stores the end of the conversion in the
format string by calculating it with the starting pos and format_size.
Format_size is the amount of characters used for the conversion.
Ex: "%-11.6s" uses 7 characters, starting at % and ending at s+1.
*/

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

/*
del_conv gets called when deleting a conversion from a linked list,
freeing whatever has been allocated.
*/

void	del_conv(void *conv)
{
	if (((t_conv *)conv)->output)
		free(((t_conv *)conv)->output);
	free(conv);
}

/*
parse_convs loops through the format string, parsing a conversion
for every % character it finds. All conversions get added to a
linked list: t_list convs. This lists ends with a conversion of type
'\0', with a format_size of 0. In case the parsing fails, the linked
list gets cleared and freed, and the function will return a NULL pointer.
*/

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
