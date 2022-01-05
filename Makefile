NAME	= minishell
incs	= -I libft -I readline-8.1.1/include
libs	= libft/libft.a readline-8.1.1/lib/* -lncurses
objs	= src/main.o \
		  src/executor.o \
		  src/pipex_utils.o

CFLAGS	= -Wall -Wextra -Werror $(incs)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(objs)
	gcc $^ $(libs) -o $@

clean:
	rm -f $(objs)

fclean: clean
	rm -f $(NAME)

re: fclean all
