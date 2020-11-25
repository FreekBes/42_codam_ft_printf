# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fbes <fbes@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/25 17:36:28 by fbes          #+#    #+#                  #
#    Updated: 2020/11/25 19:30:49 by fbes          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		libftprintf.a
SRCS =		ft_printf.c conversions.c
OBJS =		$(SRCS:.c=.o)
CFLAGS =	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft bonus
	ar rc $(NAME) $(OBJS) libft/libft.a

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

test: $(NAME)
	gcc -fsanitize=address main.c libft/libft.a libftprintf.a
	clear
	./a.out
	rm -f a.out

.PHONY: all clean fclean re
