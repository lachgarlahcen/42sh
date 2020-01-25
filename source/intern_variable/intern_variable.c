/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intern_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 22:14:22 by hastid            #+#    #+#             */
/*   Updated: 2020/01/19 05:19:04 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intern_variable.h"

int		check_variable(t_var **var,char *value)
{
	int	i;

	if (!ft_isalpha(value[0]) && value[0] != '_')
		return (1);
	i = 1;
	while (value[i] && value[i] != '=')
	{
		if (!ft_isalnum(value[i]) && value[i] != '_')
			return (1);
		i++;
	}
	if (add_elem(var, value))
		return (1);
	return (0);
}

void	ft_putvar(t_var *var)
{
	while (var)
	{
		ft_putendl(var->value);
		var = var->next;
	}
}

int		ft_unset(t_var **var, char **args)
{
	int		i;

	i = 0;
	if (args[i])
	{
		while (args[i])
			del_elem(var, args[i++]);
	}
	else
		ft_putendl("not enough arguments");
	//	ft_perror(args[0], "not enough arguments", 1);
	return (0);
}

int		ft_set(t_var **var, char **args)
{
	int	i;

	ft_putvar(*var);
	return (0);
}

char	*ft_getvar(t_var *var, char *name)
{
	while (var)
	{
		if (!ft_cmpvar(name, var->value))
			return (ft_strchr(var->value, '=') + 1);
		var = var->next;
	}
	return (0);
}

t_var	*init_variable(char **env)
{
	int		i;
	t_var	*var;

	i = 0;
	var = 0;
	while (env && env[i])
	{
		if (add_to_var(&var, env[i]))
			return (0);
		i++;
	}
	return (var);
}
