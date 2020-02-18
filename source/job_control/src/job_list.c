/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 01:41:09 by hastid            #+#    #+#             */
/*   Updated: 2020/02/18 06:54:52 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

static t_job	*add_job(t_proc *p, pid_t pgid, int bg)
{
	t_job	*j;

	if (!(j = (t_job *)malloc(sizeof(t_job))))
		return (0);
	j->p = p;
	j->pgid = pgid;
	j->notified = 0;
	if (bg)
		j->id = g_jobs.id++;
	else
		j->id = 0;
	
	j->next = 0;
	return (j);
}

void delete_job(pid_t pgid)
{
	t_job *j;
	t_job *prev;

	j = g_jobs.f_job;
	prev = NULL;
	while (j->pgid != pgid && j->next != NULL)
	{
		prev = j;
		j = j->next;
	}
	if (j->pgid == pgid)
	{
		if (prev)
		{
			prev->next = j->next;
		}
		else
		{
			g_jobs.f_job = j->next;
		}
		free_job(j);
	}
}

t_job			*add_jobs(t_proc *p, pid_t pgid, int bg)
{
	t_job	*temp;

	if (g_jobs.f_job)
	{
		temp = g_jobs.f_job;
		while (temp->next)
			temp = temp->next;
		return ((temp->next = add_job(p, pgid, bg)));
	}
	return ((g_jobs.f_job = add_job(p, pgid, bg)));
}

void			free_job(t_job *j)
{
	free_process(j->p);
	ft_memdel((void**)&j);
}

void			free_jobs(void)
{
	t_job	*tp;

	while (g_jobs.f_job)
	{
		tp = g_jobs.f_job->next;
		free_process(g_jobs.f_job->p);
		ft_memdel((void**)&g_jobs.f_job);
		g_jobs.f_job = tp;
	}
	g_jobs.f_job = 0;
}
