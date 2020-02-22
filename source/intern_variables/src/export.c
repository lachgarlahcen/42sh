/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 22:42:08 by hastid            #+#    #+#             */
/*   Updated: 2020/02/22 22:44:37 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intern_variables.h"

static int	export_variables(char *name)
{
	int		i;
	t_var	*v;
	t_var	*tp;
	char	*tmp;

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
	if (!tp)
	{
		tmp = ft_strjoin(name, "=");
		set_variable(tmp, 1, 0);
		ft_memdel((void **)&tmp);
	}
	return (0);
}

static void	put_export(void)
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
	if (args[1] && ft_strcmp(args[1], "-p"))
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
				ret = 1;
		}
	}
	else
		put_export();
	return (ret);
}
