/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_buil_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:29:59 by hastid            #+#    #+#             */
/*   Updated: 2020/02/22 22:35:40 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd_builtin.h"
#include <sys/stat.h>

int		isdir(char *path);

int			ft_perror_cd(char *s, char *str, int ret)
{
	ft_putstr_fd("21sh: ", 2);
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
		pwd = strjoin_free("OLDPWD=",pwd,0,1);
		set_variable(pwd, 1, 0);
		pwd = strjoin_free("PWD=",pwd,0,1);
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
		pwd = strjoin_free("OLDPWD=",pwd,0,1);
		set_variable(pwd, 1, 0);
		tp = strjoin_free("PWD=",tp,0,1);
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

	ft_bzero(mybuf,PATH_MAX);
	readlink(tmp,mybuf,PATH_MAX);
	return(mybuf);
}

void		built_cd_p(char **args,char *dir, char *tmp)
{
	struct stat buf;
	char *mybuf;

	if (args[2] && lstat(args[2], &buf) == -1)
		return ;
	if ((buf.st_mode & S_IFMT) == S_IFLNK && isdir(args[2]))
	{
		if (args[2][0] != '/')
		{
			if (!(dir = get_variable("PWD")))
				return ((void)ft_perror_cd("env", ": pwd not exists", 1));
			dir = strjoin_free(dir,"/", 1, 0);
			tmp = ft_strjoin(dir, args[2]);
			free(dir);
			mybuf = read_link(tmp);
			free(tmp);
		}
		else
			mybuf = read_link(args[2]);
		if (args[2][0] == '/' && S_ISLNK(buf.st_mode) && mybuf[0] != '/' )
			chdir(args[2]);
		change_dir(mybuf);
	}
	else
		built_cd(args+1);
}

int			arraylen(char **args)
{
	int i;

	i = 0;
	while(args && *args)
	{
		args++;
		i++;
	}
	return(i);
}

int			built_cd(char **args)
{
	char	*dir;
	int 	len;

	len = arraylen(args);
	// printf("len : %d \n",len);
	if (args[1] && ft_strequ(args[1], "-P")) // noureddine
		built_cd_p(args,NULL,NULL);
	else if (args[1] && ft_strequ(args[1], "-L")) 
		built_cd(args+1);
	else if (args[1])
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
		else if (!access(dir, F_OK) && access(dir,X_OK))
			ft_perror_cd(dir, ": Permission Denied", 1);
		else if (!access(dir, F_OK))
			ft_perror_cd(dir, ": Not a directory", 1);
		else
			ft_perror_cd(dir, ": No such file or directory", 1);
	}
	else if ((dir = get_variable("HOME")) && !access(dir, F_OK) && !access(dir, X_OK))
	{
		change_dir(dir);
	}
	else
		ft_perror_cd("env", ": Home not exists", 1);
	return (0);
}

int		isdir(char *path)
{
	DIR *dir;
	struct stat buf;

	dir = opendir(path);
	if (dir != 0)
	{
		closedir(dir);
		return (1);
	}
	if (lstat(path, &buf) == -1)
		return(0);
	else
	{
		if ((buf.st_mode & S_IFMT) == S_IFDIR && (buf.st_mode & S_IXUSR))
			return(1);
	}
	return (0);
}
