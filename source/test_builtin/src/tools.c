/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 01:34:18 by nsaber            #+#    #+#             */
/*   Updated: 2020/02/25 05:30:54 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_builtin.h"

char		file_type(mode_t st_mode)
{
	if ((st_mode & S_IFMT) == S_IFIFO)
		return ('p');
	if ((st_mode & S_IFMT) == S_IFCHR)
		return ('c');
	if ((st_mode & S_IFMT) == S_IFDIR)
		return ('d');
	if ((st_mode & S_IFMT) == S_IFBLK)
		return ('b');
	if ((st_mode & S_IFMT) == S_IFREG)
		return ('-');
	if ((st_mode & S_IFMT) == S_IFLNK)
		return ('l');
	if ((st_mode & S_IFMT) == S_IFSOCK)
		return ('s');
	return ('?');
}

int			ft_arraylen(char **argv)
{
	int i;

	i = 0;
	while (*argv)
	{
		argv++;
		i++;
	}
	return (i);
}

int			builtin_test_4(void)
{
	ft_putendl_fd("test: too many arguments", 2);
	return (2);
}
