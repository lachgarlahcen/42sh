/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:23:31 by aihya             #+#    #+#             */
/*   Updated: 2020/02/25 19:42:59 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		set_name_value(char *arg, char **name, char **value)
{
	int		index;

	index = 0;
	while (arg[index] && arg[index] != '=')
	{
		ft_strappend(name, arg[index], TRUE);
		index++;
	}
	if (arg[index] && arg[index] == '=' && *name != NULL)
		index++;
	while (arg[index])
	{
		ft_strappend(value, arg[index], TRUE);
		index++;
	}
}

static int	valid_alias_name(char *name)
{
	int		index;

	index = 0;
	while (name && name[index])
	{
		if (name[index] == '$' || name[index] == '/')
			return (0);
		index++;
	}
	return (1);
}

static void	set_alias(char *arg, int *status)
{
	size_t	old;
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	set_name_value(arg, &name, &value);
	old = aliases_counter(0);
	if (name == NULL)
	{
		if (is_alias(value) == NULL)
			*status = err_msg("alias", value, "Not found");
		else
			print_alias(value, FALSE);
	}
	else if (!valid_alias_name(name))
		*status = err_msg("alias", name, "Invalid alias name");
	else if (save_alias(name, value) == 0)
		*status = err_msg("alias", name, "Cannot save alias");
	ft_strdel(&name);
	ft_strdel(&value);
}

static void	set_individual_aliases(char **args, int *status)
{
	int		index;

	index = 0;
	while (args[index])
	{
		if (ft_strchr(args[index], '='))
			set_alias(args[index], status);
		else if (find_htnode(aliases(FALSE), args[index]) == NULL)
			*status = err_msg("alias", args[index], "Not found");
		else
			print_alias(args[index], FALSE);
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
