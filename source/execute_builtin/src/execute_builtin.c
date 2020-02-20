/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 04:36:08 by hastid            #+#    #+#             */
/*   Updated: 2020/02/20 04:15:36 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_builtin.h"

void	execute_exit(char **args)
{
	int	ex;

	ex = 0;
	if (args[1])
		ex = ft_atoi(args[1]);
	exit(ex);
}

int		is_builtin(char *exec)
{
	if (!ft_strcmp("cd", exec))
		return (1);
	else if (!ft_strcmp("fg", exec))
		return (1);
	else if (!ft_strcmp("bg", exec))
		return (1);
	else if (!ft_strcmp("fc", exec))
		return (0);
	else if (!ft_strcmp("set", exec))
		return (1);
	else if (!ft_strcmp("test", exec))
		return (1);
	else if (!ft_strcmp("jobs", exec))
		return (1);
	else if (!ft_strcmp("hash", exec))
		return (0);
	else if (!ft_strcmp("unset", exec))
		return (1);
	else if (!ft_strcmp("exit", exec))
		return (1);
	else if (!ft_strcmp("export", exec))
		return (1);
	/*	else if (!ft_strcmp("echo", *args))
		execute_echo();
		*/
	else if (!ft_strcmp("type", exec))
		return (1);
	else if (!ft_strcmp("alias", exec))
		return (1);
	else if (!ft_strcmp("unalias", exec))
		return (1);
	return (0);

}

int		execute_builtin(char **args)
{
	/*
	   else if (!ft_strcmp("fc", *args))
	   execute_fd();
	   */
	/*	else if (!ft_strcmp("echo", *args))
		execute_echo();
		*/
	if (!ft_strcmp("type", *args))
		return (type(args));
	else if (!ft_strcmp("hash", *args))
	  return (hash(args));
	else if (!ft_strcmp("alias", *args))
		return (alias(args));
	else if (!ft_strcmp("unalias", *args))
		return (unalias(args));
	else if (!ft_strcmp("cd", *args))
		built_cd(args);
	else if (!ft_strcmp("set", *args))
		put_variables();
	else if (!ft_strcmp("exit", *args))
		execute_exit(args);
	else if (!ft_strcmp("test", *args))
		execute_test(args);
	else if (!ft_strcmp("jobs", *args))
		execute_jobs(args);
	else if (!ft_strcmp("fg", *args))
		execute_fg(args);
	else if (!ft_strcmp("bg", *args))
		execute_bg(args);
	else if (!ft_strcmp("unset", *args))
		return (unset_variables(args));
	else if (!ft_strcmp("export", *args))
		return (execute_export(args));
	return (0);
}
