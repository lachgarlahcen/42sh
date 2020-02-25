/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 01:23:31 by nsaber            #+#    #+#             */
/*   Updated: 2020/02/25 05:14:50 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_builtin.h"

int			test_options_exclamation(char **argv)
{
	return (test_options_z(argv));
}

int			test_options_check(t_option *table, char **argv)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (ft_strequ(table[i].option, argv[1]))
			return (table[i].f(argv));
		i++;
	}
	ft_putstr_fd(argv[1], 2);
	ft_putendl_fd(" unary option not found", 2);
	return (2);
}

int			test_options(char **argv)
{
	static t_option		table[16] = {{"-b", &test_options_b},
		{"-c", &test_options_c},
		{"-d", &test_options_d},
		{"-e", &test_options_e},
		{"-f", &test_options_f},
		{"-g", &test_options_g},
		{"-L", &test_options_l},
		{"-p", &test_options_p},
		{"-r", &test_options_r},
		{"-S", &test_options_capital_s},
		{"-s", &test_options_s},
		{"-u", &test_options_u},
		{"-w", &test_options_w},
		{"-x", &test_options_x},
		{"-z", &test_options_z},
		{"!", &test_options_exclamation}
	};

	return (test_options_check(table, argv));
}
