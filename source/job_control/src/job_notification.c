/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_notification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 00:42:10 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/24 22:32:24 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

void		wait_for_job(t_job *j)
{
	int		status;
	pid_t	pid;
	t_proc	*p;

	while (1)
	{
		pid = waitpid(WAIT_ANY, &status, WUNTRACED);
		if (mark_process_status(pid, status))
			break ;
		if (job_is_stopped(j) || job_is_completed(j))
			break ;
	}
	p = j->p;
	while (p->next)
		p = p->next;
	if (WIFEXITED(p->stat))
		exit_status(WEXITSTATUS(p->stat), 1);
	else if (WIFSIGNALED(p->stat))
	{
		exit_status(WTERMSIG(p->stat) + 128, 1);
		if (WTERMSIG(p->stat) != 2)
			do_job_notification();
	}
	else if (WIFSTOPPED(j->status))
		exit_status(WSTOPSIG(p->stat) + 128, 1);
}

void		notify_exit(t_job *j, char opt)
{
	int s;

	s = WEXITSTATUS(j->status);
	if (!job_is_completed(j))
		printf_job_info(j, ft_strdup("Running"), opt);
	else if (s == 0)
		printf_job_info(j, ft_strdup("Done"), opt);
	else
		printf_job_info(j, ft_strjoin_f("Done: ", ft_itoa(s), 0, 1), opt);
}

void		notifecation_by_type(char *g_sinalmsg[], t_job *j, char option)
{
	int	s;

	s = 0;
	if (WIFEXITED(j->status) == 1)
		return (notify_exit(j, option));
	else if (WIFSIGNALED(j->status))
		s = WTERMSIG(j->status);
	else if (WIFSTOPPED(j->status))
		s = WSTOPSIG(j->status);
	else if (WIFCONTINUED(j->status))
		s = 1;
	printf_job_info(j, ft_strdup(g_sinalmsg[s]), option);
}

void		format_job_info(t_job *j, char option)
{
	static char	*g_sinalmsg[] = {
		"Done", "Hangup", "Interrupt", "Quit", "Illegal instruction",
		"Trace/breakpoint trap", "Aborted", "Bus error",
		"Floating point exception", "Killed", "User defined signal 1",
		"Segmentation fault", "User defined signal 2", "Broken pipe",
		"Alarm clock", "Terminated", "Stack fault", "Child exited", "suspended",
		"Stopped (signal)", "Stopped", "Stopped (tty input)",
		"Stopped (tty output)", "Urgent I/O condition",
		"CPU time limit exceeded", "File size limit exceeded",
		"Virtual timer expired", "Profiling timer expired", "Window changed",
		"I/O possible", "Power failure"
	};

	j->notified = 1;
	notifecation_by_type(g_sinalmsg, j, option);
}

void		do_job_notification(void)
{
	t_job *j;

	update_status();
	j = g_jobs.f_job;
	while (j)
	{
		if (!j->notified)
			format_job_info(j, 0);
		j = j->next;
	}
}
