/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:34:19 by aihya             #+#    #+#             */
/*   Updated: 2020/02/18 18:23:18 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			remove_alias(char *name)
{
	pop_htnode(aliases(FALSE), name);
	if (aliases_counter(0) > 0)
		aliases_counter(DEC);
}

void			remove_aliases(void)
{
	char		**names;
	int			index;

	names = aliases_names(FALSE);
	index = 0;
	while (names[index])
	{
		remove_alias(names[index]);
		index++;
	}
}

static int		a_option(char **args, int *status, int *last_index)
{
	int		i;
	int		remove_all;

	i = 0;
	remove_all = 0;
	while (args[i] && args[i][0] == '-' && ft_strlen(args[i]) > 1)
	{
		if (ft_strequ(args[i], "--"))
		{
			*last_index = ++i;
			break ;
		}
		if (invalid_option(args[i], 'a', "unalias"))
		{
			*status = unalias_usage();
			break ;
		}
		remove_all = 1;
		i++;
	}
	return (remove_all);
}

static void		set_individual_aliases(char **args, int *status)
{
	int	remove_all;
	int	index;

	index = 0;
	remove_all = a_option(args, status, &index);
	if (*status)
		return ;
	if (remove_all)
		remove_aliases();
	else
	{
		while (args[index])
		{
			if (is_alias(args[index]) == NULL)
				*status = err_msg("unalias", args[index], "Not found");
			else
				remove_alias(args[index]);
			index++;
		}
	}
}

int				unalias(char **args)
{
	int		status;

	status = 0;
	if (ft_chain_size(args) == 1)
		status = unalias_usage();
	else
		set_individual_aliases(args + 1, &status);
	return (status);
}
