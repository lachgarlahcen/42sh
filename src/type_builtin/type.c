/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 19:21:27 by aihya             #+#    #+#             */
/*   Updated: 2020/02/17 19:45:33 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Options: None.

#include "sh.h"

static int	test_alias(char *arg)
{
	char	*tmp;
	int		ret;

	ret = 0;
	tmp = is_alias(arg);
	if (tmp != NULL)
	{
		ft_putstr(arg);
		ft_putstr(" is aliased to ");
		ft_putendl(tmp);
		ret = 1;
	}
	ft_strdel(&tmp);
	return (ret);
}

static int	test_binary(char *arg)
{
	char	*tmp;
	int		ret;

	ret = 0;
	tmp = is_binary(arg);
	if (tmp != NULL)
	{
		ft_putstr(arg);
		ft_putstr(" is ");
		ft_putendl(tmp);
		ret = 1;
	}
	ft_strdel(&tmp);
	return (ret);
}

int			type(char **args)
{
	int		index;
	int		status;

	status = 0;
	index = 0;
	while (args[index])
	{
		if (!test_alias(args[index]) && !test_binary(args[index]))
			status = err_msg("type", args[index], "Not found");
		index++;
	}
}
