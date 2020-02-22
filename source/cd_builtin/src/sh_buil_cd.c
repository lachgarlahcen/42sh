/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_buil_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:29:59 by hastid            #+#    #+#             */
/*   Updated: 2020/02/22 23:56:22 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd_builtin.h"
#include <sys/stat.h>

int			ft_perror_cd(char *s, char *str, int ret)
{
	ft_putstr_fd("42sh: ", 2);
	if (s)
		ft_putstr_fd(s, 2);
	ft_putendl_fd(str, 2);
	return (ret);
}

static int	change_dir_b(char *dir)
{
	char	*pwd;

	chdir(dir);
	if ((pwd = getcwd(0, 0)))
	{
		pwd = strjoin_free("OLDPWD=", pwd, 0, 1);
		set_variable(pwd, 1, 0);
		pwd = strjoin_free("PWD=", pwd, 0, 1);
		set_variable(pwd, 1, 0);
		ft_memdel((void **)&pwd);
	}
	return (0);
}

static int	change_dir_a(char *dir)
{
	char	*tp;
	char	*pwd;

	if ((tp = get_variable("PWD")))
	{
		if (!(pwd = tp))
			return (0);
	}
	else if (!(pwd = getcwd(0, 0)))
		return (0);
	if ((tp = path_of_link(dir, pwd)))
	{
		chdir(tp);
		pwd = strjoin_free("OLDPWD=", pwd, 0, 1);
		set_variable(pwd, 1, 0);
		tp = strjoin_free("PWD=", tp, 0, 1);
		set_variable(tp, 1, 0);
		ft_memdel((void **)&tp);
	}
	else
		return (0);
	ft_memdel((void **)&pwd);
	return (1);
}

static int	change_dir(char *dir)
{
	if (!change_dir_a(dir))
		change_dir_b(dir);
	return (0);
}

char		*read_link(char *tmp)
{
	static char mybuf[PATH_MAX];

	ft_bzero(mybuf, PATH_MAX);
	readlink(tmp, mybuf, PATH_MAX);
	return (mybuf);
}

int		cd_link_dir(char *dir, char *mybuf, char **args, struct stat *buf)
{
	char *tmp;

	if (args[2][0] != '/')
	{
		if (!(dir = get_variable("PWD")))
			return (ft_perror_cd("env", ": pwd not exists", 1));
		dir = strjoin_free(dir, "/", 1, 0);
		tmp = ft_strjoin(dir, args[2]);
		free(dir);
		mybuf = read_link(tmp);
		free(tmp);
	}
	else
		mybuf = read_link(args[2]);
	if (args[2][0] == '/' && S_ISLNK(buf->st_mode) && mybuf[0] != '/')
		chdir(args[2]);
	change_dir(mybuf);
	return (0);
}

int		built_cd_p(char **args, char *dir)
{
	struct stat			buf;

	if (args[2] && lstat(args[2], &buf) == -1)
	{
		if (!access(dir, F_OK) && access(dir, X_OK))
			return (ft_perror_cd(dir, ": Permission Denied", 1));
		else if (!access(dir, F_OK))
			return (ft_perror_cd(dir, ": Not a directory", 1));
		else
			return (ft_perror_cd(dir, ": No such file or directory", 1));
	}
	if ((buf.st_mode & S_IFMT) == S_IFLNK && isdir(args[2]))
		return (cd_link_dir(dir, NULL, args, &buf));
	else
		return (built_cd(args + 1));
}

int			cd_arg(char **args, char *dir)
{
	if (!ft_strcmp("-", args[1]))
	{
		if (!(dir = get_variable("OLDPWD")))
			return (ft_perror_cd("env", ": Oldpwd not exists", 1));
	}
	else
		dir = args[1];
	if (isdir(dir))
		change_dir(dir);
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
		return (built_cd_p(args, NULL));
	else if (args[1] && ft_strequ(args[1], "-L"))
		built_cd(args + 1);
	else if (args[1])
		return (cd_arg(args, dir));
	else if ((dir = get_variable("HOME"))
			&& !access(dir, F_OK) && !access(dir, X_OK))
		change_dir(dir);
	else
		return (ft_perror_cd("env", ": Home not exists", 1));
	return (0);
}

int		isdir(char *path)
{
	DIR			*dir;
	struct stat	buf;

	dir = opendir(path);
	if (dir != 0)
	{
		closedir(dir);
		return (1);
	}
	if (lstat(path, &buf) == -1)
		return (0);
	else if ((buf.st_mode & S_IFMT) == S_IFDIR && (buf.st_mode & S_IXUSR))
		return (1);
	return (0);
}
