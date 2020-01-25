/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern_variable.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 22:11:57 by hastid            #+#    #+#             */
/*   Updated: 2020/01/19 02:07:51 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_VARIABLE_H
# define INTERN_VARIABLE_H

# include "../../libft/libft.h"

typedef struct	s_var
{
	int				id;
	char			*value;
	struct s_var	*next;
}				t_var;

t_var			*init_variable(char **env);
int				ft_set(t_var **var, char **args);
int				ft_unset(t_var **var, char **args);
char			*ft_getvar(t_var *var, char *name);

int				add_elem(t_var **var, char *value);
int				del_elem(t_var **var, char *value);
int				add_to_var(t_var **var, char *value);

int				ft_cmpvar(char *s1, char *s2);

#endif
