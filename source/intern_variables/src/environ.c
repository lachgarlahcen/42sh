/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:39:18 by hastid            #+#    #+#             */
/*   Updated: 2020/02/22 22:44:13 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intern_variables.h"

static char		*get_env_variable(char *name, char *value)
{
	char	*var;

	var = 0;
	if (name)
	{
		var = ft_strjoin(name, "=");
		if (value)
			var = strjoin_free(var, value, 1, 0);
	}
	return (var);
}

static t_var	*get_env_elements(void)
{
	t_var	*tp;
	t_var	*env;

	env = 0;
	tp = get_intern_variables(0, 0);
	while (tp)
	{
		if (tp->id)
			add_to_var(&env, tp->name, tp->value, 1);
		tp = tp->next;
	}
	tp = get_temp_variables(0, 0);
	while (tp)
	{
		add_elem(&env, tp->name, tp->value, 1);
		tp = tp->next;
	}
	return (env);
}

static void		free_env(t_var *var)
{
	t_var	*tmp;

	while (var)
	{
		tmp = var->next;
		ft_memdel((void **)&(var->name));
		ft_memdel((void **)&(var->value));
		ft_memdel((void **)&var);
		var = tmp;
	}
}

char			**get_env_variables(void)
{
	int		l;
	t_var	*tmp;
	t_var	*var;
	char	**env;

	l = 0;
	var = get_env_elements();
	tmp = var;
	while (tmp)
	{
		l++;
		tmp = tmp->next;
	}
	if (!l || !(env = (char **)malloc(sizeof(char *) * (l + 1))))
		return (0);
	l = 0;
	tmp = var;
	while (tmp)
	{
		env[l++] = get_env_variable(tmp->name, tmp->value);
		tmp = tmp->next;
	}
	env[l] = 0;
	free_env(var);
	return (env);
}
