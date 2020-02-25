/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 05:18:24 by hastid            #+#    #+#             */
/*   Updated: 2020/02/25 05:29:07 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_builtin.h"

int			builtin_test_1(char *str, int len)
{
	if (len == 0 || str[0] == '\0')
		return (1);
	return (0);
}

int			builtin_test_2(char **argv)
{
	return (test_options(argv));
}

int			builtin_test_3(char **argv)
{
	return (test_cmp(argv));
}

int			builtin_test(int len, char **argv)
{
	int ret;

	if (len <= 1)
	{
		ret = builtin_test_1(argv[len], len);
	}
	else if (len == 2)
	{
		ret = builtin_test_2(argv);
	}
	else if (len == 3)
	{
		ret = builtin_test_3(argv);
	}
	else
	{
		ret = builtin_test_4();
	}
	return (ret);
}

int			execute_test(char **argv)
{
	int ret;
	int arraylen;

	arraylen = ft_arraylen(argv);
	ret = builtin_test(arraylen - 1, argv);
	exit_status(ret, 1);
	return (ret);
}
