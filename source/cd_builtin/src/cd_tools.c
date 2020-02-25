/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 21:50:06 by nsaber            #+#    #+#             */
/*   Updated: 2020/02/25 04:26:26 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd_builtin.h"

int	change_dir_b(char *dir)
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

int	change_dir_a(char *dir)
{
	char	*tp;
	char	*pwd;

	if (!dir)
		return (1);
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

int	change_dir(char *dir)
{
	if (!change_dir_a(dir))
		change_dir_b(dir);
	ft_memdel((void **)&dir);
	return (0);
}

int			isdir(char *path)
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

int			ft_perror_cd(char *s, char *str, int ret)
{
	ft_putstr_fd("42sh: ", 2);
	if (s)
	{
		ft_putstr_fd(s, 2);
		ft_memdel((void **)&s);		
	}
	ft_putendl_fd(str, 2);
	return (ret);
}
