/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_cmdl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 01:02:55 by hastid            #+#    #+#             */
/*   Updated: 2020/02/23 01:13:30 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intern_variables.h"

int		unset_variables(char **args)
{
	int		i;
	int		ret;
	int		check;
	t_var	*var;

	ret = 0;
	if (args[1])
	{
		i = 0;
		check = 0;
		var = get_intern_variables(0, 0);
		while (args[++i])
		{
			if ((check = check_name_variables(args[i], 0)))
				ret = 1;
			if (check)
				continue ;
			del_elem(&var, args[i]);
		}
		get_intern_variables(&var, 1);
	}
	return (ret);
}

int		set_variable(char *arg, int id, int temp)
{
	int		co;
	char	*name;
	t_var	*var;

	if (arg)
	{
		var = temp ? get_temp_variables(0, 0) : get_intern_variables(0, 0);
		if (check_name_variables(arg, 1))
			return (1);
		co = 0;
		arg = delet_quotes(arg);
		while (arg[co] != '=')
			co++;
		if (!(name = ft_strsub(arg, 0, co)))
			return (0);
		if (add_elem(&var, name, arg + co + 1, id))
			return (0);
		ft_memdel((void **)&name);
		if (temp)
			get_temp_variables(&var, 1);
		else
			get_intern_variables(&var, 1);
		ft_memdel((void **)&arg);
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

	var = get_temp_variables(0, 0);
	while (var)
	{
		if (!ft_strcmp(name, var->name))
			return (ft_strdup(var->value));
		var = var->next;
	}
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
