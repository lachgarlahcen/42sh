/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:39:18 by hastid            #+#    #+#             */
/*   Updated: 2020/02/08 03:46:25 by hastid           ###   ########.fr       */
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

char	**get_env_variables(void)
{
	int	l;
	t_var   *tmp;
	char    **env;

	l = 0;
	tmp = get_intern_variables(0, 0);
	while (tmp)
	{
		if (tmp->id)
			l++;
		tmp =  tmp->next;
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
