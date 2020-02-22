/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:23:31 by aihya             #+#    #+#             */
/*   Updated: 2020/02/22 15:39:50 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		set_name_value(char *arg, char **name, char **value)
{
	int		index;
	char	*tmp_name;
	char	*tmp_value;

	index = 0;
	tmp_name = NULL;
	tmp_value = NULL;
	while (arg[index] && arg[index] != '=')
	{
		ft_strappend(&tmp_name, arg[index], TRUE);
		index++;
	}
	if (tmp_name != NULL && arg[index] == '=')
		index++;
	while (arg[index])
	{
		ft_strappend(&tmp_value, arg[index], TRUE);
		index++;
	}
	*name = tmp_name;
	*value = tmp_value;
}

int			valid_alias_name(char *name)
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

	set_name_value(arg, &name, &value);
	old = aliases_counter(0);
	if (name == NULL)
	{
		if (is_alias(value) == NULL)
			*status = err_msg("alias", value, "Not found");
		else
			print_alias(value, FALSE);
		ft_strdel(&value);
		return ;
	}
	else if (save_alias(name, value) == 0)
		*status = err_msg("alias", name, "Cannot save alias");
	if (old == aliases_counter(0))
		ft_strdel(&name);
	else
	{
		ft_strdel(&name);
		ft_strdel(&value);
	}
}

static void	set_individual_aliases(char **args, int *status)
{
	int		index;

	index = 0;
	while (args[index])
	{
		if (ft_strchr(args[index], '='))
			set_alias(args[index], status);
		else if (is_alias(args[index]) == NULL)
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
	{
		set_individual_aliases(args + 1, &status);
		aliases_names(TRUE);
	}
	return (status);
}
