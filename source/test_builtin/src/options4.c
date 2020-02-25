/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 04:56:27 by nsaber            #+#    #+#             */
/*   Updated: 2020/02/25 04:57:36 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_builtin.h"

int			test_options_s(char **argv)
{
	struct stat buf;

	if (lstat(argv[2], &buf) == -1 || buf.st_size <= 0)
		return (1);
	return (0);
}

int			test_options_u(char **argv)
{
	struct stat buf;

	if (lstat(argv[2], &buf) == -1 || !(buf.st_mode & S_ISUID) ? 1 : 0)
		return (1);
	return (0);
}

int			test_options_w(char **argv)
{
	struct stat buf;

	if (lstat(argv[2], &buf) == -1 || !(buf.st_mode & S_IWUSR))
		return (1);
	return (0);
}

int			test_options_x(char **argv)
{
	struct stat buf;

	if (lstat(argv[2], &buf) == -1 || !(buf.st_mode & S_IXUSR))
		return (1);
	return (0);
}

int			test_options_z(char **argv)
{
	int len;

	len = ft_strlen(argv[2]);
	return (!(len == 0));
}
