/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:18:53 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/25 07:09:50 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"


int			job_arg_option(char *option, char **args)
{
	int i;

	i = 0;
	while (args[1][++i])
	{
		*option = args[1][i];
		if (!(args[1][i] == 'l' || args[1][i] == 'p'))
		{
			*option = args[1][i];
			ft_putendl_fd("jobs: invalid option : jobs [-lp]", 2);
			return (1);
		}
	}
	if (args[2])
	{
		execute_jobs(args + 1);
		*option = 0;
		return (0);
	}
	job_printing(*option);
	return (0);
}

int			job_arg(char **args, char *option, int i)
{
	t_job	*jj;
	t_job	*j;
	int		percent;

	j = g_jobs.f_job;
	jj = j;
	args[1][0] == '%' ? percent = 1 : 0;
	while (j)
	{
		if (args[i] && (ft_strequ(args[i], j->cmd) ||
		(ft_isdigits(args[i]) && ft_atoi(args[i] + percent) == j->id)))
		{
			i++;
			format_job_info(j, *option);
			j = jj;
		}
		else
			j = j->next;
		if (!j && args[i])
		{
			ft_putendl_fd("jobs: job not found", 2);
			return (1);
		}
	}
	return (0);
}

int			execute_jobs(char **args)
{
	t_job		*j;
	int			i;
	static char	option = 0;

	update_status();
	i = 0;
	j = g_jobs.f_job;
	if (args[1] && args[1][0] == '-' && job_arg_option(&option, args))
		return (1);
	else if (args[1] && job_arg(args, &option, 1))
		return(1);
	else
		job_printing(option);
	option = 0;
	return(0);
}

int			execute_fg(char **args)
{
	t_job	*j;

	if (getpid() != g_shell_pgid)
	{
		ft_putendl_fd("fg: no job control", 2);
		return (1);
	}
	j = g_jobs.f_job;
	if (args [1] && args[1][0] == '-' && args[1][1])
	{
		ft_putendl_fd("fg: invalid option fg [job_spec]", 2);
		return(1);
	}
	if (!j)
	{
		ft_putendl_fd("fg: current: no such job", 2);
		return(1);
	}
	if (check_ctr_jobs_args(args, &j, "42sh : fg", 0))
		return(1);
	put_job_in_foreground(j, 1);
	return(0);
}

int			execute_bg(char **args)
{
		t_job	*j;

	if (getpid() != g_shell_pgid)
	{
		ft_putendl_fd("bg: no job control", 2);
		return (1);
	}
	j = g_jobs.f_job;
	if (args [1] && args[1][0] == '-' && args[1][1])
	{
		ft_putendl_fd("bg: invalid option bg [job_spec]", 2);
		return(1);
	}
	if (!j)
	{
		ft_putendl_fd("bg: current: no such job", 2);
		return(1);
	}
	if (check_ctr_jobs_args(args, &j, "42sh : bg", 0))
		return(1);
	put_job_in_background(j, 1);
	return(0);
}

