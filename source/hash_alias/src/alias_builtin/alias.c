/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 18:51:01 by aihya             #+#    #+#             */
/*   Updated: 2020/02/21 19:57:30 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:23:31 by aihya             #+#    #+#             */
/*   Updated: 2020/02/21 18:50:59 by aihya            ###   ########.fr       */
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
	if (*name != NULL && arg[index] == '=')
		index++;
	while (arg[index])
	{
		ft_strappend(value, arg[index], TRUE);
		index++;
	}
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

static void	set_alias(char *name, char *value, int *status)
{
	char	*tmp;

	tmp = NULL;
	if (name == NULL)
	{
		if ((tmp = is_alias(value)) == NULL)
			*status = err_msg("alias", value, "Not found");
		else
			print_alias(value, FALSE);
	}
	else if (save_alias(name, value) == 0)
		*status = err_msg("alias", name, "Cannot save alias (probable memory lack)");
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
		set_name_value(args[index], &name, &value);
		if (ft_strchr(args[index], '='))
			set_alias(name, value, status);
		else if ((value = is_alias(args[index])) == NULL)
			*status = err_msg("alias", name, "Not found");
		else
			print_alias(args[index], FALSE);
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
	{
		set_individual_aliases(args + 1, &status);
		aliases_names(TRUE);
	}
	return (status);
}
