/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 05:10:31 by hastid            #+#    #+#             */
/*   Updated: 2020/02/12 23:46:37 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_BUILTIN_H
# define TEST_BUILTIN_H

#include "shell.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

typedef struct  s_option
{
    char    *option;
    int     (*f)(char **argv);
}               t_option;

typedef struct  s_cmp
{
    char    *operator;
    int     (*f) (char **argv);
}               t_cmp;


char	file_type(mode_t st_mode);
int     test_options(char **argv);
int     test_cmp(char **argv);
int     builtin_test_1(char *str, int len);

int		execute_test(char **args);

#endif
