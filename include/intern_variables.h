/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern_variables.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 01:22:06 by hastid            #+#    #+#             */
/*   Updated: 2020/02/05 03:17:04 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_VARIABLES_H
# define INTERN_VARIABLES_H

# include "shell.h"

typedef struct	s_var
{
	char			*name;
	char			*value;
	struct s_var	*next;
}				t_var;

int				del_elem(t_var **var, char *name);
int				add_elem(t_var **var, char *name, char *value);
int				add_to_var(t_var **var, char *name, char *value);

void			put_variables(void);
int				set_variable(char *arg);
char			*get_variable(char *name);
int				unset_variables(char **args);
t_var			*creat_variables(char **env);

void			free_variables(void);
void			init_variables(char **env);

t_var			*get_intern_variables(t_var **v, int check);

#endif
