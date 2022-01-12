# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/09 13:50:14 by skoh              #+#    #+#              #
#    Updated: 2022/01/13 03:00:49 by skoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
incs	= -I libft -I readline-7.0/include
objs	= src/main.o \
		  src/pipeline.o \
		  src/executable.o \
		  src/builtins.o \
		  src/get_cmds.o \
		  src/utils.o \
		  src/redirection.o \
		  src/heredoc.o \
		  src/environment.o

LDLIBS	= libft/libft.a readline-7.0/lib/*.a -lncurses
LDFLAGS = -fsanitize=address -g3
CFLAGS	= -Wall -Wextra -Werror $(LDFLAGS) $(incs)

.PHONY: all clean fclean re

all: $(NAME)

src/get_cmds.o:
	gcc -c src/get_cmds.c $(LDFLAGS) $(incs) -o $@

$(NAME): $(objs)
	$(LINK.o) $^ $(LDLIBS) -o $@

clean:
	rm -f $(objs)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette src

$(objs): |readline-7.0

readline-7.0:
	curl -LO https://ftp.gnu.org/gnu/readline/readline-7.0.tar.gz
	@echo "750d437185286f40a369e1e4f4764eda932b9459b5ec9a731628393dd3d32334  readline-7.0.tar.gz" | shasum -c
	@tar xzf readline-7.0.tar.gz
	@echo Compiling libreadline...  \
	&& cd $@ \
	&& ./configure --prefix=$$(pwd) &>/dev/null \
	&& make &>/dev/null \
	&& make install &>/dev/null
	@rm readline-7.0.tar.gz
