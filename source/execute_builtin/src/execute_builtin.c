/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 04:36:08 by hastid            #+#    #+#             */
/*   Updated: 2020/02/23 16:31:17 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_builtin.h"
#include <limits.h>

int		ft_perror_buil(char *error)
{
	ft_putstr("42sh: ");
	ft_putendl(error);
	return (1);
}

int64_t	ft_atoll(char *str, int *check)
{
	int			s;
	int			i;
	uint64_t	r;

	i = 0;
	r = 0;
	s = 1;
	while (str[i] == ' ' || str[i] == '\n')
		i++;
	if (str[i] == '-')
	{
		s = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		if (r > 9223372036854775807)
			*check = 1;
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]) && str[i] != ' ' && str[i] != '\n')
			*check = 1;
	return ((int64_t)(r * s));
}

int		execute_exit(char **args)
{
	int			check;
	uint64_t	value;

	check = 0;
	if (args[1])
	{
		if (args[2] && is_number(args[1]))
			return (ft_perror_buil("exit: too many arguments"));
		value = ft_atoll(args[1], &check);
		g_exit = 1;
		g_stat =  check ? 255 : value % 256;
		ft_putendl("exit");
		if (check)
			return (ft_perror_buil("exit: numeric argument required"));
	}
	else
		g_exit = 1;
	return (g_stat);
}

static int	execute_echo(char **args)
{
	int i;
	int check;

	i = 1;
	if (write(1, 0, 0) == -1)
	{
		ft_putendl_fd("42sh: echo: write error: Bad file descriptor", 2);
		return (1);
	}
	while (args[i] && !ft_strcmp("-n", args[i]))
		i++;
	check = (i != 1) ? 0 : 1;
	while (args[i])
	{
		ft_putstr(args[i]);
		if (args[i + 1] && args[i] != '\0')
			ft_putstr(" ");
		i++;
	}
	if (check)
		ft_putchar('\n');
	return (0);
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
		return (1);
	else if (!ft_strcmp("set", exec))
		return (1);
	else if (!ft_strcmp("test", exec))
		return (1);
	else if (!ft_strcmp("jobs", exec))
		return (1);
	else if (!ft_strcmp("hash", exec))
		return (1);
	else if (!ft_strcmp("unset", exec))
		return (1);
	else if (!ft_strcmp("exit", exec))
		return (1);
	else if (!ft_strcmp("export", exec))
		return (1);
	else if (!ft_strcmp("echo", exec))
		return (1);
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
	if (!ft_strcmp("echo", *args))
		return (execute_echo(args));
	else if (!ft_strcmp("type", *args))
		return (type(args));
	else if (!ft_strcmp("hash", *args))
		return (hash(args));
	else if (!ft_strcmp("alias", *args))
		return (alias(args));
	else if (!ft_strcmp("unalias", *args))
		return (unalias(args));
	else if (!ft_strcmp("cd", *args))
		return (built_cd(args));
	else if (!ft_strcmp("set", *args))
		put_variables();
	else if (!ft_strcmp("exit", *args))
		return (execute_exit(args));
	else if (!ft_strcmp("test", *args))
		return (execute_test(args));
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
	else if (!ft_strcmp("fc", *args))
		return (ft_fc(args));
	return (0);
}
