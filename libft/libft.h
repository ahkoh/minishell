/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skoh <skoh@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 02:43:33 by Koh               #+#    #+#             */
/*   Updated: 2021/11/04 00:57:42 by skoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;

}					t_list;

void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int i, char *c));
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
int		ft_split_count(char **tab);
void	ft_split_free(char ***tab);

char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		ft_atoi_try(const char *str, int *out);

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(const char *s, int fd);
void	ft_putendl_fd(const char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstiter_param(
			t_list *lst,
			void (*f)(void *content, int index, void *param),
			void *param);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void	ft_lstsort(t_list *lst, int (*f)(void *, void *));
void	*ft_lsttoarray(t_list *lst);

int		ft_list_push(t_list **head, void *content);
int		ft_list_enqueue(t_list **head, void *content);
int		ft_list_enqueue_unique(
			t_list **head, void *content, int (*cmp)(void *new, void *cur));
void	*ft_list_pop(t_list **head);
void	*ft_list_pop_last(t_list **head);

int		ft_starts_with(const char *str, const char *prefix);
int		ft_ends_with(const char *str, const char *suffix);
int		ft_loop(int **vals, int cnt1, int cnt2, int cnt3);
void	**ft_malloc_2d(int rows, int columns, int size);
void	ft_swap(void *a, void *b, unsigned int size);

int		get_next_line(int fd, char **line);
int		ft_printf(const char *format, ...)
		__attribute__((format(printf, 1, 2)));
int		ft_printf_fd(int fd, const char *format, ...)
		__attribute__((format(printf, 2, 3)));
#endif
