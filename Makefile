# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/09 13:50:14 by skoh              #+#    #+#              #
#    Updated: 2022/01/20 09:00:02 by skoh             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
incs	= -I includes -I libft -I readline-7.0/include
objs	= src/main.o \
		  src/executor/pipeline.o \
		  src/executor/syntax.o \
		  src/executor/executable.o \
		  src/executor/utils.o \
		  src/executor/redirection.o \
		  src/executor/heredoc.o \
		  src/executor/fd_helper.o \
		  src/executor/cleanup.o \
		  src/executor/run_script.o \
		  src/builtin/cd.o \
		  src/builtin/echo.o \
		  src/builtin/env.o \
		  src/builtin/quit.o \
		  src/builtin/export.o \
		  src/builtin/pwd.o \
		  src/builtin/unset.o \
		  src/builtin/debug.o \
		  src/builtin/builtin.o \
		  src/parse/expand_cmd.o \
		  src/parse/free_cmd.o \
		  src/parse/get_cmd.o \
		  src/parse/split_arg.o \
		  src/parse/split_arg_malloc.o \
		  src/parse/split_cmds.o \
		  src/parse/utils.o \

libft	= libft/libft.a
LDLIBS	= readline-7.0/lib/*.a -lncurses
LDFLAGS = -fsanitize=address -g3
CFLAGS	= -Wall -Wextra -Werror $(LDFLAGS) $(incs)


all: $(NAME)

$(NAME): $(objs) $(libft)
	$(LINK.o) $^ $(LDLIBS) -o $@

clean:
	rm -f $(objs)

fclean: clean
	rm -f $(NAME)

re: fclean all

$(libft):
	make -C libft

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

readline-8.1:
	curl -LO https://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz
	@echo "f8ceb4ee131e3232226a17f51b164afc46cd0b9e6cef344be87c65962cb82b02  readline-8.1.tar.gz" | shasum -c
	@tar xzf readline-8.1.tar.gz
	@echo Compiling libreadline...  \
	&& cd $@ \
	&& ./configure --prefix=$$(pwd) &>/dev/null \
	&& make &>/dev/null \
	&& make install &>/dev/null
	@rm readline-8.1.tar.gz

.PHONY: all clean fclean re h b x v test

norm:
	norminette libft
	norminette src
	norminette includes

h help:
	@echo 'make x => remove AddressSanitizer to work with leaks'
	@echo 'make b => compare bash'
	@echo 'make v => valgrind test'
	@echo 'make t => test result'

b:
	PS1='[$$?]$$(pwd)> ' bash

x: $(NAME)
	make re LDFLAGS="-g3"
	cp minishell x

v: x
	valgrind --leak-check=full --show-leak-kinds=all \
	--track-origins=yes --trace-children=yes ./minishell
	# --suppressions=readline.supp \
	# --gen-suppressions=all --log-file=minimalraw.log \
	# leaks -q -atExit -- ./minishell -c 'echo $$?'
	# valgrind --leak-check=yes ./minishell -c 'echo $$?'

t:
	less -r minishell_test.out
	less -r minishell_tester.out

test: x
	git clone https://github.com/thallard/minishell_tester.git test
	cd test && bash test.sh --valgrind
