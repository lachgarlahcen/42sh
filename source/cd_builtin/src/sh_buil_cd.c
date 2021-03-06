/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_buil_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:29:59 by hastid            #+#    #+#             */
/*   Updated: 2020/02/25 19:19:05 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd_builtin.h"

char		*read_link(char *tmp)
{
	static char mybuf[PATH_MAX];

	ft_bzero(mybuf, PATH_MAX);
	readlink(tmp, mybuf, PATH_MAX);
	return (ft_strdup(mybuf));
}

int			cd_link_dir(char *dir, char *mybuf, char **args, struct stat *buf)
{
	if (args[2][0] != '/')
	{
		if (!(dir = get_variable("PWD")))
			return (ft_perror_cd(ft_strdup("env"), ": pwd not exists", 1));
		mybuf = strjoin_free(dir, "/", 1, 0);
		dir = ft_strjoin(mybuf, args[2]);
		ft_memdel((void **)&mybuf);
		mybuf = read_link(dir);
		ft_memdel((void **)&dir);
	}
	else
		mybuf = read_link(args[2]);
	if (args[2][0] == '/' && S_ISLNK(buf->st_mode) && mybuf[0] != '/')
	{
		chdir(args[2]);
		ft_memdel((void **)&mybuf);
		if (!(mybuf = getcwd(NULL, 0)))
			return (1);
		ft_memdel((void **)&mybuf);
	}
	else
	{
		change_dir(mybuf);
	}
	return (0);
}

int			built_cd_p(char **args, char *dir, char *tp)
{
	struct stat	buf;

	if (args[2] && lstat(args[2], &buf) == -1)
	{
		if (!access(args[2], F_OK) && access(args[2], X_OK))
			return (ft_perror_cd(ft_strdup(args[2]), ": Permission Denied", 1));
		else if (!access(args[2], F_OK))
			return (ft_perror_cd(ft_strdup(args[2]), ": Not a directory", 1));
		else
			return (ft_perror_cd(ft_strdup(args[2]),
			": No such file or directory", 1));
	}
	if ((buf.st_mode & S_IFMT) == S_IFLNK && isdir(args[2]))
		return (cd_link_dir(dir, NULL, args, &buf));
	else
	{
		if (!(dir = getcwd(0, 0)))
			return (1);
		tp = strjoin_free("PWD=", dir, 0, 1);
		set_variable(tp, 1, 0);
		ft_memdel((void **)&tp);
		return (built_cd(args + 1));
	}
}

int			cd_arg(char **args, char *dir)
{
	if (!ft_strcmp("-", args[1]))
	{
		if (!(dir = get_variable("OLDPWD")))
			return (ft_perror_cd(ft_strdup("env"), ": Oldpwd not exists", 1));
	}
	else
		dir = ft_strdup(args[1]);
	if (isdir(dir))
	{
		change_dir(dir);
	}
	else if (!access(dir, F_OK) && access(dir, X_OK))
		return (ft_perror_cd(dir, ": Permission Denied", 1));
	else if (!access(dir, F_OK))
		return (ft_perror_cd(dir, ": Not a directory", 1));
	else
		return (ft_perror_cd(dir, ": No such file or directory", 1));
	return (0);
}

int			built_cd(char **args)
{
	char	*dir;

	dir = NULL;
	if (args[1] && ft_strequ(args[1], "-P"))
		return (built_cd_p(args, NULL, NULL));
	else if (args[1] && ft_strequ(args[1], "-L"))
		built_cd(args + 1);
	else if (args[1])
		return (cd_arg(args, dir));
	else if ((dir = get_variable("HOME"))
			&& !access(dir, F_OK) && !access(dir, X_OK))
		change_dir(dir);
	else
		return (ft_perror_cd(ft_strdup("env"), ": Home not exists", 1));
	return (0);
}
