/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 22:11:54 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/11 03:31:22 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

# define VALID_CONVERSIONS "cspdiuxX"
# define VALID_FIELDS "-0"
# define VALID_FIELDS_DIG "-0123456789.*"

typedef struct s_conv
{
	const char		*position;
	const char		*end;
	int				width;
	int				precision;
	char			prepend;
	int				alignment;
	char			type;
	void			*input;
	char			*output;
}					t_conv;

void				del_conv(void *conv);
t_list				*parse_convs(va_list *params, const char *s);
int					handle_conv(t_conv *conv);
int					ft_printf(const char *n, ...);

#endif
