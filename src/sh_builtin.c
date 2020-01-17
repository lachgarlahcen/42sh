/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 05:57:21 by hastid            #+#    #+#             */
/*   Updated: 2019/12/19 14:37:04 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	built_echo(char **args)
{
	int i;
	int check;

	check = 1;
	if (args[1])
	{
		i = 1;
		if (!ft_strcmp("-n", args[i]))
		{
			while (args[i] && !ft_strcmp("-n", args[i]))
				i++;
			check = 0;
		}
		while (args[i])
		{
			ft_putstr(args[i]);
			if (args[i + 1] && args[i] != '\0')
				ft_putstr(" ");
			i++;
		}
	}
	if (check)
		ft_putchar('\n');
	return (0);
}

int			check_built(char *str)
{
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	if (!ft_strcmp(str, "setenv"))
		return (1);
	if (!ft_strcmp(str, "unsetenv"))
		return (1);
	return (0);
}

static int	execute_builtin(char **args, t_env **env)
{
	if (!ft_strcmp(args[0], "cd"))
		built_cd(args, env);
	if (!ft_strcmp(args[0], "env"))
		ft_putenv(*env);
	if (!ft_strcmp(args[0], "echo"))
		built_echo(args);
	if (!ft_strcmp(args[0], "setenv"))
		ft_setenv(env, args);
	if (!ft_strcmp(args[0], "unsetenv"))
		ft_unsetenv(env, args);
	return (0);
}

int			execute_builtins(t_tok *t, t_env **env)
{
	char	**as;
	t_file	*fil;

	if (save_file(&fil, 0, 1, 2))
		return (1);
	if (!duplicate(t))
	{
		if (!(as = args_execve(t)))
			return (1);
		execute_builtin(as, env);
		free_tab(as);
	}
	free_file(fil);
	return (0);
}
