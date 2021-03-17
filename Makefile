# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fbes <fbes@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2020/11/25 17:36:28 by fbes          #+#    #+#                  #
#    Updated: 2021/03/17 15:30:55 by fbes          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		libftprintf.a

SRCS =		ft_printf.c conversions.c input_output.c

OBJS =		$(SRCS:.c=.o)

CFLAGS =	-Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS) libft/libft.a
	cp libft/libft.a $(NAME)
	ar rc $(NAME) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

libft/libft.a: FORCE
	make -C libft

FORCE:

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean:
	rm -f $(OBJS)
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

test: $(NAME)
	gcc -fsanitize=address main.c libftprintf.a
	clear
	./a.out
	rm -f a.out

.PHONY: all clean fclean re FORCE
