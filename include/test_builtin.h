/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 05:10:31 by hastid            #+#    #+#             */
/*   Updated: 2020/02/25 05:30:33 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_BUILTIN_H
# define TEST_BUILTIN_H

# include "shell.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>

typedef struct	s_option
{
	char		*option;
	int			(*f)(char **argv);
}				t_option;

typedef struct	s_cmp
{
	char		*operator;
	int			(*f) (char **argv);
}				t_cmp;

char			file_type(mode_t st_mode);
int				test_options(char **argv);
int				test_cmp(char **argv);
int				builtin_test_1(char *str, int len);
int				execute_test(char **args);
int				test_options_s(char **argv);
int				test_options_u(char **argv);
int				test_options_w(char **argv);
int				test_options_x(char **argv);
int				test_options_z(char **argv);
int				test_options_capital_s(char **argv);
int				test_options_r(char **argv);
int				test_options_p(char **argv);
int				test_options_l(char **argv);
int				test_options_g(char **argv);
int				test_options_b(char **argv);
int				test_options_c(char **argv);
int				test_options_d(char **argv);
int				test_options_e(char **argv);
int				test_options_f(char **argv);
int				test_string_eq(char **argv);
int				test_string_neq(char **argv);
int				test_int_eq(char **argv);
int				test_int_ne(char **argv);
int				builtin_test_4(void);
int				ft_arraylen(char **argv);

#endif
