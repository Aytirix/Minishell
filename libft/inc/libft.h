/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbislimi <dbislimi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 09:18:10 by dbislimi          #+#    #+#             */
/*   Updated: 2024/07/26 17:08:48 by dbislimi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int					ft_atoi(const char *nptr);
long				ft_atol(const char *nptr);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
size_t				ft_strlen(const char *s);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strcat(char *s1, char *s2);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
void				ft_bzero(void *s, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strrchr(const char *s, int c);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoinf(char const *s1, char const *s2, int s_free);
char				*ft_strjoinwsep(int size, char **strs, char *sep);
char				*ft_strtrim(char const *s, char const *set);
char				**ft_split(char const *s, char c);
char				**free_all_split(char **tab);
int					count_words(char const *s, char c);
void				free_tab(char **tab);
char				*ft_free(char *tab);
void				ft_strcpy(char *dest, char *src);
char				*ft_itoa(int n);
char				*ft_itoa_base(int n, char *base);
size_t				nbsize(long nb);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
int					is_whitespace(char c);
char				*ft_joinf(const char *str, ...);
int					ft_fprintf(int fd, const char *str, ...);
char				*ft_strjoinc(char c);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

#endif