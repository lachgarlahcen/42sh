/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 23:15:26 by aihya             #+#    #+#             */
/*   Updated: 2020/02/18 18:30:01 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFF_SIZE 256
# define BEGINING 0
# define LAST_POS -1

typedef struct	s_node
{
	char			*content;
	struct s_node	*next;
}				t_node;

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

typedef struct	s_lst
{
	char			*cut;
	int				fd;
	struct s_lst	*next;
}				t_lst;

size_t			ft_char_count(char *str, char c);
int				ft_strisempty(char *str);
char			*ft_strappend(char **a_s1, char c, int overwrite);
int				ft_isalphanumeric(char c);
void			ft_print_chain(char **chain, char *del);
char			**ft_strsplit_del(char *str, char *del);
char			*ft_next_word(char *str, char *del, int reset_val);
size_t			ft_count_words(const char *str, const char *del);
int				ft_strcount(char **s);
size_t			ft_wordlen(const char *s, char c);
int				ft_words(char const *s, char c);
int				ft_abs(int n);
int				ft_atoi(const char *str);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putendl(char const *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strojoin(char **s1, char *s2, int overwrite);
char			*ft_strtrim(char const *s);
char			*ft_strrev(char const *s);
char			*ft_strstr(const char *haystack, const char *needle);
int				ft_strisnum(const char *str);
char			**ft_new_chain(char **base);
char			**ft_sort_chain(char **chain, int direction);
void			ft_chain_push(char ***a_chain, char *entry);
size_t			ft_chain_size(char **chain);
char			**ft_chain_cpy(char **chain);
void			ft_chain_free(char ***a_chain);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
size_t			ft_strlen(const char *s);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_intlen(int n);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t len);
void			ft_putchar(char c);
void			ft_putstr(char const *s);
void			*ft_memset(void *b, int c, size_t len);
void			ft_bzero(void *s, size_t n);
char			*ft_itoa(int n);
char			*ft_itoa_base(long long value, int base);
char			*ft_strnstr(const char *haystack, const char *needle,
				size_t len);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
char			*ft_ctos(const char c);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *c, int fd);
void			ft_putnbr(int n);
void			ft_putnbr_fd(int n, int fd);
char			*ft_strsjoin(const char *s1, const char *s2, const char *dl);
int				ft_begins_with(const char *haystack, const char *needle);
char			**ft_strsplit(char const *s, char c);
size_t			ft_strmax(char **arr);
size_t			ft_strmin(char **arr);

#endif
