/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 04:55:00 by nsaber            #+#    #+#             */
/*   Updated: 2020/02/25 04:55:26 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_builtin.h"

int			test_options_b(char **argv)
{
	struct stat buf;

	if (lstat(argv[2], &buf) == -1 || file_type(buf.st_mode) != 'b')
		return (1);
	return (0);
}

int			test_options_c(char **argv)
{
	struct stat buf;

	if (lstat(argv[2], &buf) == -1 || file_type(buf.st_mode) != 'c')
		return (1);
	return (0);
}

int			test_options_d(char **argv)
{
	struct stat buf;

	if (lstat(argv[2], &buf) == -1 || file_type(buf.st_mode) != 'd')
		return (1);
	return (0);
}

int			test_options_e(char **argv)
{
	struct stat buf;

	if (lstat(argv[2], &buf) == -1)
		return (1);
	return (0);
}

int			test_options_f(char **argv)
{
	struct stat buf;

	if (lstat(argv[2], &buf) == -1 || file_type(buf.st_mode) != '-')
		return (1);
	return (0);
}
