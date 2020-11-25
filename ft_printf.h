/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 17:44:06 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/25 19:11:05 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

# define VALID_CONVERSIONS "cspdiuxX%"

enum	conversion_type{c_undefined = 0, c_c = 'c', c_s = 's', c_p = 'p', c_d = 'd', c_i = 'i', c_u = 'u', c_x = 'x', c_X = 'X', c_perc = '%'};

typedef struct				s_conversion
{
	const char				*position;
	void					*input;
	char					*output;
	int						field_width;
	enum conversion_type	type;
	struct s_conversion		*next;
}							t_conversion;

t_list		*parse_conversions(const char *s);
int			ft_printf(const char *, ...);

#endif
