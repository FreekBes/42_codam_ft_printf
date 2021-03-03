/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 17:44:06 by fbes          #+#    #+#                 */
/*   Updated: 2021/03/03 19:36:41 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

# define VALID_CONVERSIONS "cspdiuxX%"
# define VALID_FIELDS "-0"
# define VALID_FIELDS_DIG "-1234567890.*"

typedef struct s_conv
{
	const char		*position;
	const char		*end;
	int				width;
	int				precision;
	char			prepend;
	int				alignment;
	char			type;
	struct s_conv	*next;
}					t_conv;

t_list				*parse_convs(const char *s);
int					handle_conv(t_conv *conv, void *input);
int					ft_printf(const char *n, ...);
void				print_conv(t_conv *conv, void *input);

#endif
