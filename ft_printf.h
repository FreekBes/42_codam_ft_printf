/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fbes <fbes@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/25 17:44:06 by fbes          #+#    #+#                 */
/*   Updated: 2020/11/25 20:51:08 by fbes          ########   odam.nl         */
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
	void			*input;
	char			*output;
	int				width;
	int				precision;
	char			type;
	struct s_conv	*next;
}					t_conv;

t_list		*parse_convs(const char *s);
int			ft_printf(const char *n, ...);

#endif
