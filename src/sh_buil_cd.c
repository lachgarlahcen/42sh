/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_buil_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 16:29:59 by hastid            #+#    #+#             */
/*   Updated: 2019/12/14 02:46:53 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	change_dir_b(char *dir, t_env **env)
{
	char	*pwd;

	chdir(dir);
	if ((pwd = getcwd(0, 0)))
	{
		add_elem(env, "OLDPWD", pwd);
		add_elem(env, "PWD", pwd);
		ft_memdel((void **)&pwd);
	}
	return (0);
}

static int	change_dir_a(char *dir, t_env **env)
{
	char	*tp;
	char	*pwd;

	if ((tp = ft_getenv(*env, "PWD")))
	{
		if (!(pwd = ft_strdup(tp)))
			return (0);
	}
	else if (!(pwd = getcwd(0, 0)))
		return (0);
	if ((tp = path_of_link(dir, pwd)))
	{
		chdir(tp);
		add_elem(env, "OLDPWD", pwd);
		add_elem(env, "PWD", tp);
		ft_memdel((void **)&tp);
	}
	else
		return (0);
	ft_memdel((void **)&pwd);
	return (1);
}

static int	change_dir(char *dir, t_env **env)
{
	if (!change_dir_a(dir, env))
		change_dir_b(dir, env);
	return (0);
}

int			built_cd(char **args, t_env **env)
{
	char	*dir;

	if (args[1])
	{
		if (!ft_strcmp("-", args[1]))
		{
			if (!(dir = ft_getenv(*env, "OLDPWD")))
				return (ft_perror("env", ": Oldpwd not exists", 1));
		}
		else
			dir = args[1];
		if (isdir(dir))
			change_dir(dir, env);
		else if (!access(dir, F_OK))
			ft_perror(dir, ": Not a directory", 1);
		else
			ft_perror(dir, ": No such file or directory", 1);
	}
	else if ((dir = ft_getenv(*env, "HOME")))
		change_dir(dir, env);
	else
		ft_perror("env", ": Home not exists", 1);
	return (0);
}
