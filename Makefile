NAME	= minishell
incs	= -I libft -I readline-8.1.1/include
objs	= src/main.o \
		  src/executor.o \
		  src/pipex_utils.o

LDLIBS	= libft/libft.a readline-8.1.1/lib/* -lncurses
LDFLAGS = -fsanitize=address
CFLAGS	= -Wall -Wextra -Werror $(LDFLAGS) $(incs)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(objs)
	$(LINK.o) $^ $(LDLIBS) -o $@

clean:
	rm -f $(objs)

fclean: clean
	rm -f $(NAME)

re: fclean all
