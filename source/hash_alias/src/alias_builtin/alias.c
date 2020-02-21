/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:23:31 by aihya             #+#    #+#             */
/*   Updated: 2020/02/21 15:12:30 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		set_name_value(char *arg, char **name, char **value)
{
	int		index;

	index = 0;
	name = NULL;
	value = NULL;
	while (arg[index] && arg[index] != '=')
	{
		ft_strappend(name, arg[index], TRUE);
		index++;
	}
	if (arg[index] == '=')
	{
		index++;
		while (arg[index])
		{
			ft_strappend(value, arg[index], TRUE);
			index++;
		}
	}
}

int			valid_alias_name(char *name)
{
	int		index;

	index = 0;
	while (name[index])
	{
		if (name[index] == '$' || name[index] == '/')
			return (0);
		index++;
	}
	return (1);
}

static void	set_individual_aliases(char **args, int *status)
{
	int		index;
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	index = 0;
	while (args[index])
	{
		if (ft_strchr(args[index], '='))
		{
			set_name_value(args[index], &name, &value);
			if (!valid_alias_name(name))
				*status = err_msg("alias", name, "Invalid alias name");
			else
				save_alias(name, value);
		}
		else if ((value = is_alias(args[index])) == NULL)
			*status = err_msg("alias", args[index], "Not found");
		else
			print_alias(args[index]);
		ft_strdel(&name);
		ft_strdel(&value);
		index++;
	}
}

int			alias(char **args)
{
	int		status;

	status = 0;
	if (ft_chain_size(args) == 1)
		print_all_alias();
	else
		set_individual_aliases(args + 1, &status);
	return (status);
}
