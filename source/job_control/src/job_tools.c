/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 22:29:49 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/25 06:22:04 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

void		mark_process(t_proc *p, int status)
{
	p->stat = status;
	if (WIFEXITED(status) == 1)
		p->c = 1;
	else if (WIFSIGNALED(status))
		p->c = 1;
	else if (WIFSTOPPED(status))
		p->s = 1;
	else if (WIFCONTINUED(status))
		p->s = 0;
}

int			mark_process_status(pid_t pid, int status)
{
	t_job	*j;
	t_proc	*p;

	j = g_jobs.f_job;
	if (pid > 0)
	{
		while (j)
		{
			p = j->p;
			while (p)
			{
				if (p->pid == pid)
				{
					mark_process(p, status);
					j->notified = 0;
					if (!p->next)
						j->status = p->stat;
					return (0);
				}
				p = p->next;
			}
			j = j->next;
		}
	}
	return (1);
}

void		printf_job_info(t_job *j, char *status, char opt)
{
	if (opt == 0)
		ft_printf("[%d]%c %s\t\t%s\n", j->id, j->sign, status, j->name);
	else if (opt == 'l')
		ft_printf("[%d]%c  %ld  %s\t\t%s\n", j->id,
				j->sign, (long)j->pgid, status, j->name);
	else if (opt == 'p')
		ft_printf("%d\n", j->pgid);
	ft_strdel(&status);
	if (job_is_completed(j))
		delete_job(j->pgid);
}

void		update_status(void)
{
	int		status;
	pid_t	pid;
	t_job	*j;

	j = g_jobs.f_job;
	while (1337)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED | WNOHANG);
		if (mark_process_status(pid, status))
			break ;
	}
}

void		job_printing(char option)
{
	t_job *j;

	j = g_jobs.f_job;
	while (j)
	{
		j->notified = 1;
		format_job_info(j, option);
		j = j->next;
		if (!(option == 'l' || option == 'p' || option == 0))
			break ;
	}
}
