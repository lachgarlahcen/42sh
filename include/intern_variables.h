/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern_variables.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 01:22:06 by hastid            #+#    #+#             */
/*   Updated: 2020/02/23 19:05:10 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_VARIABLES_H
# define INTERN_VARIABLES_H

# include "shell.h"
# include "struct_shell.h"

int		del_elem(t_var **var, char *name);
int		add_elem(t_var **var, char *name, char *value, int id);
int		add_to_var(t_var **var, char *name, char *value, int id);

int		check_name_variables(char *name, int check);

void	put_variables(void);
int		set_variable(char *arg, int id, int temp);
char	*get_variable(char *name);
int		unset_variables(char **args);
t_var	*creat_variables(char **env);

int		execute_export(char **args);

void	free_variables(void);
void	free_temp_variables(void);

void	init_variables(char **env);

char	**get_env_variables(void);
t_var	*get_intern_variables(t_var **v, int check);
t_var	*get_temp_variables(t_var **v, int check);

#endif
