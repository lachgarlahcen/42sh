/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_cmp_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 05:22:40 by nsaber            #+#    #+#             */
/*   Updated: 2020/02/25 05:23:18 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_builtin.h"

int			test_string_eq(char **argv)
{
	return (!ft_strequ(argv[1], argv[3]));
}

int			test_string_neq(char **argv)
{
	return (ft_strequ(argv[1], argv[3]));
}

int			test_int_eq(char **argv)
{
	int i;
	int j;

	i = 0;
	j = 1;
	while (argv[j][i])
	{
		if (!ft_isdigit(argv[j][i]))
		{
			ft_putendl_fd("integer expression expected", 2);
			return (2);
		}
		i++;
		if (j != 3 && !argv[j][i])
		{
			j = 3;
			i = 0;
		}
	}
	i = ft_atoi(argv[1]);
	j = ft_atoi(argv[3]);
	return (!(i == j));
}

int			test_int_ne(char **argv)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (argv[j][i])
	{
		if (!ft_isdigit(argv[j][i]))
		{
			ft_putendl_fd("integer expression expected", 2);
			return (2);
		}
		i++;
		if (j != 3 && !argv[j][i])
		{
			j = 3;
			i = 0;
		}
	}
	return (!test_int_eq(argv));
}
