/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:23:31 by aihya             #+#    #+#             */
/*   Updated: 2020/02/14 21:19:09 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_htnode		**aliases(int init)
{
	static t_htnode	**hashtable;

	if (init == TRUE)
		hashtable = init_hashtable();
	return (hashtable);
}

size_t			aliases_counter(int action)
{
	static size_t	counter = 0;
	
	if (action == INC)
		counter++;
	else if (action == DEC && counter > 0)
		counter--;
	return (counter);
}

int				save_alias(char *name, char *value)
{
	t_htnode	*alias;

	if (name == NULL || value == NULL)
		return (0);
	alias = new_htnode(name, value);
	if (alias == NULL)
		return (0);
	if (push_htnode(aliases(FALSE), &alias))
	{
		aliases_counter(INC);
		aliases_names(TRUE);
	}
	return (1);
}

char			*is_alias(char *name)
{
	t_htnode	*alias;

	if ((alias = find_htnode(aliases(FALSE), name)) == NULL)
		return (NULL);
	return (alias->value);
}

void			unalias(char *name)
{
	pop_htnode(aliases(FALSE), name);
	if (aliases_counter(0) > 0)
		aliases_counter(DEC);
}

// Get names of aliases sorted in ascending order || Reset the table of names
// when new element is introduced.
char			**aliases_names(int reset)
{
	static char	**names = NULL;

	if (reset == TRUE)
	{
		if (names != NULL)
			ft_chain_free(&names);
		names = get_names(aliases(FALSE), aliases_counter(0));
	}
	return (names);
}

void			set_name_value(char *arg, char **name, char **value)
{
	int		index;

	index = 0;
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

int				alias(char **args)
{
	int		index;
	char	*name;
	char	*value;
	int		status;

	index = 1;
	status = 0;
	name = NULL;
	value = NULL;
	while (args[index])
	{
		if (ft_strchr(args[index], '='))
		{
			set_name_value(args[index], &name, &value);
			status = save_alias(name, value) == 0 ? 1 : status;
			ft_strdel(&name);
			ft_strdel(&value);
		}
		else if ((value = is_alias(args[index])) != NULL)
			printf("alias %s='%s'\n", args[index], value);
		else if ((status = 1))
			dprintf(2, "alias: %s: not found\n", args[index]);
		index++;
	}
	return (status);
}