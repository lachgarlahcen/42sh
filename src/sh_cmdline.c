/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmdline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:20:06 by hastid            #+#    #+#             */
/*   Updated: 2019/12/19 14:56:00 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static char	*check_file(char *tmp)
{
	if (isdir(tmp))
		ft_perror(tmp, ": is a directory", 0);
	else if (!access(tmp, X_OK))
		return (ft_strdup(tmp));
	else
		ft_perror(tmp, ": Permission denied", 0);
	return (0);
}

static char	*check_exe(char *str, char **path)
{
	int		i;
	char	*tp1;
	char	*tp2;

	i = 0;
	while (path[i])
	{
		if (!(tp1 = ft_strjoin(path[i], "/")))
			return (0);
		if (!(tp2 = ft_strjoin(tp1, str)))
			return (0);
		ft_memdel((void **)&tp1);
		if (!access(tp2, F_OK))
		{
			tp1 = check_file(tp2);
			ft_memdel((void **)&tp2);
			return (tp1);
		}
		ft_memdel((void **)&tp2);
		i++;
	}
	return (0);
}

static char	*search_in_path(char *exe, t_env *env)
{
	char	*tp;
	char	**path;

	tp = 0;
	if (!ft_strcmp(exe, ".") || !ft_strcmp(exe, "..") || ft_strchr(exe, '/'))
		return (tp);
	if ((path = ft_strsplit(ft_getenv(env, "PATH"), ':')))
	{
		tp = check_exe(exe, path);
		free_tab(path);
	}
	return (tp);
}

char		*search_executable(char *exe, t_env *env)
{
	char	*tp;

	if (exe[0])
	{
		if ((tp = search_in_path(exe, env)))
			return (tp);
		if (!access(exe, F_OK))
			return (check_file(exe));
	}
	ft_perror(exe, ": command not found", 1);
	return (0);
}
