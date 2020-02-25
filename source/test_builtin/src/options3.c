/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 04:55:47 by nsaber            #+#    #+#             */
/*   Updated: 2020/02/25 04:56:19 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_builtin.h"

int			test_options_g(char **argv)
{
	struct stat buf;

	if (lstat(argv[2], &buf) == -1 || !(buf.st_mode & S_ISGID) ? 1 : 0)
		return (1);
	return (0);
}

int			test_options_l(char **argv)
{
	struct stat buf;

	if (lstat(argv[2], &buf) == -1 || file_type(buf.st_mode) != 'l')
		return (1);
	return (0);
}

int			test_options_p(char **argv)
{
	struct stat buf;

	if (lstat(argv[2], &buf) == -1 || file_type(buf.st_mode) != 'p')
		return (1);
	return (0);
}

int			test_options_r(char **argv)
{
	struct stat buf;

	if (lstat(argv[2], &buf) == -1 || !(buf.st_mode & S_IRUSR))
		return (1);
	return (0);
}

int			test_options_capital_s(char **argv)
{
	struct stat buf;

	if (lstat(argv[2], &buf) == -1 || file_type(buf.st_mode) != 's')
		return (1);
	return (0);
}
