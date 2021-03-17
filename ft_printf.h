/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/10 22:11:54 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/17 16:10:43 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

# define VALID_CONVERSIONS "cspdiuxX"
# define VALID_FIELDS "-0"
# define VALID_FIELDS_DIG "-0123456789.*"
# define HEX_UP "0123456789ABCDEF"
# define HEX_DOWN "0123456789abcdef"
# define DECIMAL "0123456789"

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

t_conv				*new_conv(const char *pos, char c, int format_size);
void				del_conv(void *conv);
int					parse_conv(va_list *params, t_list **convs, const char **s);
t_list				*parse_convs(va_list *params, const char *s);
int					handle_precision(t_conv *conv);
int					write_conv(t_conv *conv);
int					ft_printf(const char *n, ...);

#endif
