/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:39:18 by hastid            #+#    #+#             */
/*   Updated: 2020/02/17 03:28:20 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intern_variables.h"

static char	*get_env_variable(char *name, char *value)
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

char		**get_env_variables(void)
{
	int		l;
	t_var	*tmp;
	char	**env;

	l = 0;
	tmp = get_intern_variables(0, 0);
	while (tmp)
	{
		if (tmp->id)
			l++;
		tmp = tmp->next;
	}
	if (!l || !(env = (char **)malloc(sizeof(char *) * (l + 1))))
		return (0);
	l = 0;
	tmp = get_intern_variables(0, 0);
	while (tmp)
	{
		if (tmp->id)
			env[l++] = get_env_variable(tmp->name, tmp->value);
		tmp = tmp->next;
	}
	env[l] = 0;
	return (env);
}

int			export_variables(char *name)
{
	int		i;
	t_var	*v;
	t_var	*tp;

	i = 1;
	v = get_intern_variables(0, 0);
	if (check_name_variables(name, 0))
		return (1);
	tp = v;
	while (tp)
	{
		if (!ft_strcmp(tp->name, name))
			break ;
		tp = tp->next;
	}
	if (tp)
		tp->id = 1;
	return (0);
}

void		put_export(void)
{
	t_var	*v;

	v = get_intern_variables(0, 0);
	while (v)
	{
		if (v->id)
			ft_printf("export %s=\"%s\"\n", v->name, v->value);
		v = v->next;
	}
}

int			execute_export(char **args)
{
	int	i;
	int	ret;

	ret = 0;
	if (args[1])
	{
		if (!ft_strcmp(args[1], "-p"))
			put_export();
		else
		{
			i = 0;
			while (args[++i])
			{
				if (ft_strchr(args[i], '='))
				{
					if (set_variable(args[i], 1, 0))
						ret = 1;
				}
				else if (export_variables(args[i]))
					ret = 1;;
			}
		}
	}
	else
		put_export();
	return (ret);
}
