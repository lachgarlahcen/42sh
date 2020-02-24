/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 19:21:27 by aihya             #+#    #+#             */
/*   Updated: 2020/02/24 15:09:15 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	test_alias(char *arg)
{
	char	*tmp;

	tmp = is_alias(arg);
	if (tmp != NULL)
	{
		ft_printf("%s is aliased to `%s'\n", arg, tmp);
		return (1);
	}
	return (0);
}

static int	test_binary(char *arg)
{
	char	*tmp;

	tmp = is_binary(arg);
	if (tmp != NULL)
	{
		ft_printf("%s is hashed to %s\n", arg, tmp);
		return (1);
	}
	return (0);
}

static int	test_builtin(char *arg)
{
	if (is_builtin(arg))
	{
		ft_printf("%s is a builting\n", arg);
		return (1);
	}
	return (0);
}

int			type(char **args)
{
	int		index;
	int		status;
	char	*bin_path;

	status = 0;
	index = 1;
	while (args[index])
	{
		if (!test_alias(args[index])
		&& !test_binary(args[index])
		&& !test_builtin(args[index]))
		{
			if ((bin_path = get_bin_path(args[index])) == NULL)
				status = err_msg("type", args[index], "Not found");
			else
				ft_printf("%s is %s\n", args[index], bin_path);
			ft_strdel(&bin_path);
		}
		index++;
	}
	return (status);
}
