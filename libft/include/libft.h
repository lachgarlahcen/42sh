/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 12:23:05 by hastid            #+#    #+#             */
/*   Updated: 2020/02/25 05:51:11 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct	s_form
{
	int		fie;
	int		pre;
	int		poi;
	char	*flag;
	char	*leng;
}				t_form;

typedef struct	s_rep
{
	__uint64_t	man:63;
	unsigned	in_p:1;
	unsigned	exp:15;
	unsigned	sign:1;
}				t_rep;

union			u_rep
{
	t_rep		rep;
	long double	f;
};

typedef struct	s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}				t_list;

char			*ft_strojoin(char **s1, char *s2, int overwrite);
char			*ft_strappend(char **a_s1, char c, int overwrite);
void			ft_chain_free(char ***a_chain);
size_t			ft_chain_size(char **chain);
void			*ft_memset(void *str, int c, size_t n);
void			ft_bzero(void *str, size_t n);
void			*ft_memcpy(void *str1, const void *str2, size_t n);
void			*ft_memccpy(void *str1, const void *str2, int c, size_t n);
void			*ft_memmove(void *str1, const void *str2, size_t n);
void			*ft_memchr(const void *str, int c, size_t n);
int				ft_memcmp(const void *str1, const void *str2, size_t n);
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *src);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dest, const char *src, size_t n);
char			*ft_strcat(char *dest, const char *src);
char			*ft_strncat(char *dest, const char *src, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *str, int c);
char			*ft_strrchr(const char *str, int c);
char			*ft_strstr(const char *hay, const char *nee);
char			*ft_strnstr(const char *hay, const char *nee, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_atoi(const char *str);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isblank(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_strclr(char *s);
void			ft_striter(char *s, void (*f)(char *));
void			ft_striteri(char *s, void (*f)(unsigned int, char *));
char			*ft_strmap(char const *s, char (*f)(char));
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_strequ(char const *s1, char const *s2);
int				ft_strnequ(char const *s1, char const *s2, size_t n);
char			*ft_strsub(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s);
char			**ft_strsplit(char const *s, char c);
char			*ft_itoa(int n);
void			ft_putchar(char c);
void			ft_putstr(char const *str);
void			ft_putnbr(int n);
void			ft_putendl(char const *s);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char const *s, int fd);
void			ft_putendl_fd(char const *s, int fd);
void			ft_putnbr_fd(int n, int fd);
t_list			*ft_lstnew(void const *content, size_t	content_size);
void			ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void			ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void			ft_lstadd(t_list **alst, t_list *new);
void			ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

int				ft_nbrlen(int n);
size_t			ft_lstlen(t_list *lst);
void			ft_lstaddend(t_list **alst, t_list *new);

int				ft_putchar_ret(char c);
int				ft_putstr_ret(const char *str);

int				ft_printf(char *fmt, ...);
int				ft_putchar_pr(char c, t_form *frm);
int				ft_putstr_pr(char *str, t_form *frm);
int				ft_putnbr_adr(uint64_t n, t_form *frm);
void			ft_putnbr_base(uint64_t n, unsigned int base, int check);
int				ft_putwithleng(va_list ap, t_form *frm);
int				ft_putuwithleng(va_list ap, t_form *frm);
int				ft_putowithleng(va_list ap, t_form *frm);
int				ft_putxwithleng(va_list ap, t_form *frm);
int				ft_putcxwithleng(va_list ap, t_form *frm);
int				ft_putnbr_pr(int64_t nbr, t_form *frm);
int				ft_putunbr_pr(uint64_t nbr, t_form *frm);
int				ft_putonbr_pr(int64_t nbr, t_form *frm);
int				ft_putxnbr_pr(int64_t nbr, t_form *frm);
int				ft_putcxnbr_pr(int64_t nbr, t_form *frm);
int				ft_putall(t_form *frm, uint64_t n, int base, int max);
int				ft_unbrleng(uint64_t n, int base);
int				check_f(char *str, char c);
int				nbr_cnvrt(char **str);
char			*ft_strjoin_free(char *str, char c);
int				ft_putstr_err_ret(const char *str, int ret);

void			ft_free_st(t_form *frm);

#endif
