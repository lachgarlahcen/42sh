/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 19:21:27 by aihya             #+#    #+#             */
/*   Updated: 2020/02/18 18:17:03 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static int	test_alias(char *arg)
{
	char	*tmp;
	int		ret;

	ret = 0;
	tmp = is_alias(arg);
	if (tmp != NULL)
	{
		printf("%s is aliased to `%s'\n", arg, tmp);
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
		printf("%s is %s\n", arg, tmp);
		ret = 1;
	}
	ft_strdel(&tmp);
	return (ret);
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
		if (!test_alias(args[index]) && !test_binary(args[index]))
		{
			if ((bin_path = get_bin_path(args[index])) == NULL)
				status = err_msg("type", args[index], "Not found");
			else
				printf("%s is %s\n", args[index], bin_path);
			ft_strdel(&bin_path);
		}
		index++;
	}
	return (status);
}
