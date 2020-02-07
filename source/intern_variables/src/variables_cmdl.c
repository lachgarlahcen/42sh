/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_cmdl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 01:02:55 by hastid            #+#    #+#             */
/*   Updated: 2020/02/06 22:46:33 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intern_variables.h"

int		unset_variables(char **args)
{
	int		i;
	t_var	*var;

	if (args[1])
	{
		var = get_intern_variables(0, 0);
		if (!ft_isalpha(args[1][0]) && args[1][0] != '_')
			return (1);
		i = 0;
		while (args[1][++i])
			if (!ft_isalnum(args[1][i]) && args[1][i] != '_')
				return (1);
		i = 1;
		while (args[i])
			del_elem(&var, args[i++]);
		get_intern_variables(&var, 1);
	}
	return (0);
}

int		set_variable(char *arg, int id)
{
	int		i;
	int		co;
	char	*name;
	t_var	*var;

	if (arg)
	{
		var = get_intern_variables(0, 0);
		if (!ft_isalpha(arg[0]) && arg[0] != '_')
			return (1);
		i = 0;
		while (arg[++i] && arg[i] != '=')
			if (!ft_isalnum(arg[i]) && arg[i] != '_')
				return (1);
		co = 0;
		while (arg[co] != '=')
			co++;
		if (!(name = ft_strsub(arg, 0, co)))
			return (0);
		if (add_elem(&var, name, arg + co + 1, id))
			return (0);
		ft_memdel((void **)&name);
		get_intern_variables(&var, 1);
	}
	return (0);
}

void	put_variables(void)
{
	t_var	*var;

	var = get_intern_variables(0, 0);
	while (var)
	{
		ft_putstr(var->name);
		ft_putchar('=');
		ft_putendl(var->value);
		var = var->next;
	}
}

char	*get_variable(char *name)
{
	t_var	*var;

	var = get_intern_variables(0, 0);
	while (var)
	{
		if (!ft_strcmp(name, var->name))
			return (ft_strdup(var->value));
		var = var->next;
	}
	return (0);
}

t_var	*creat_variables(char **var)
{
	int		i;
	int		co;
	char	*tmp;
	char	*name;
	t_var	*my_var;

	i = 0;
	my_var = 0;
	while (var && var[i])
	{
		tmp = var[i];
		co = 0;
		while (tmp[co] != '=')
			co++;
		if (!(name = ft_strsub(tmp, 0, co)))
			return (0);
		if (add_to_var(&my_var, name, tmp + co + 1, 1))
			return (0);
		ft_memdel((void **)&name);
		i++;
	}
	return (my_var);
}
