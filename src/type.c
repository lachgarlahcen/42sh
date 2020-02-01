/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 19:21:27 by aihya             #+#    #+#             */
/*   Updated: 2020/02/01 16:19:13 by aihya            ###   ########.fr       */
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

void		type(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (!test_alias(args[i]) && !test_binary(args[i]))
		{
			ft_putstr(args[i]);
			ft_putendl(" not found");
		}
		i++;
	}
}
