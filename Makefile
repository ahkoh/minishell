# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/09 13:50:14 by skoh              #+#    #+#              #
#    Updated: 2022/01/09 13:50:15 by skoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
incs	= -I libft -I readline-8.1.1/include
objs	= src/main.o \
		  src/executor.o \
		  src/pipex_utils.o \
		  src/builtins.o \
		  src/get_cmds.o

LDLIBS	= libft/libft.a readline-8.1.1/lib/* -lncurses
LDFLAGS = -fsanitize=address -g3
CFLAGS	= -Wall -Wextra -Werror $(LDFLAGS) $(incs)

.PHONY: all clean fclean re

all: $(NAME)

src/get_cmds.o:
	gcc -c src/get_cmds.c $(LDFLAGS) -o $@

$(NAME): $(objs)
	$(LINK.o) $^ $(LDLIBS) -o $@

clean:
	rm -f $(objs)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette src
