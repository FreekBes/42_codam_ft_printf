/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 17:44:06 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/25 21:09:54 by fbes          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

# define VALID_CONVERSIONS "cspdiuxX%"
# define VALID_FIELDS "-1234567890.*"

typedef struct		s_conv
{
	const char		*position;
	const char		*end;
	int				width;
	int				precision;
	char			type;
	struct s_conv	*next;
}					t_conv;

t_list		*parse_convs(const char *s);
void		handle_conv(t_conv *conv, void *input);
int			ft_printf(const char *n, ...);

#endif
