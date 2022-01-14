# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zhliew <zhliew@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/18 00:20:02 by zhliew            #+#    #+#              #
#    Updated: 2022/01/13 11:54:23 by zhliew           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
		ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
		ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
		ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c ft_memccpy.c \
		ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
		ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
		ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c \
		ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
		ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
		ft_lstmap.c ft_lstnew.c ft_lstsize.c \
		ft_islower_bonus.c ft_isupper_bonus.c ft_memalloc_bonus.c \
		ft_putchar_bonus.c ft_putendl_bonus.c ft_putnbr_bonus.c \
		ft_putstr_bonus.c ft_strcat_bonus.c ft_strcmp_bonus.c \
		ft_strncpy_bonus.c ft_strstr_bonus.c ft_strreplace.c \
		ft_get_nb_size.c ft_strndup.c ft_isspace.c ft_shift.c \
		ft_str_qsort.c

OBJECTS	= ft_isalnum.o ft_isprint.o ft_memcmp.o  ft_putchar_fd.o ft_split.o \
		ft_strlcat.o ft_strncmp.o ft_substr.o ft_atoi.o ft_isalpha.o \
		ft_itoa.o ft_memcpy.o  ft_putendl_fd.o ft_strchr.o  ft_strlcpy.o \
		ft_strnstr.o ft_tolower.o ft_bzero.o   ft_isascii.o ft_memccpy.o \
		ft_memmove.o ft_putnbr_fd.o  ft_strdup.o  ft_strlen.o  ft_strrchr.o \
		ft_toupper.o ft_calloc.o  ft_isdigit.o ft_memchr.o  ft_memset.o  \
		ft_putstr_fd.o  ft_strjoin.o ft_strmapi.o ft_strtrim.o \
		ft_lstadd_back.o ft_lstadd_front.o ft_lstclear.o \
		ft_lstdelone.o ft_lstiter.o ft_lstlast.o \
		ft_lstmap.o ft_lstnew.o ft_lstsize.o \
		ft_islower_bonus.o ft_isupper_bonus.o ft_memalloc_bonus.o \
		ft_putchar_bonus.o ft_putendl_bonus.o ft_putnbr_bonus.o \
		ft_putstr_bonus.o ft_strcat_bonus.o ft_strcmp_bonus.o \
		ft_strncpy_bonus.o ft_strstr_bonus.o ft_strreplace.o \
		ft_get_nb_size.o ft_strndup.o ft_isspace.o ft_shift.o \
		ft_str_qsort.o

all: $(NAME)

$(NAME): $(SRCS) libft.h
	@gcc -Wall -Wextra -Werror -c $(SRCS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

clean:
	@/bin/rm -f $(OBJECTS)

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
