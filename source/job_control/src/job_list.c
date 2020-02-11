/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 01:41:09 by hastid            #+#    #+#             */
/*   Updated: 2020/02/08 01:58:17 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

static t_job	*add_job(t_proc *p, pid_t pgid)
{
	t_job	*j;

	if (!(j = (t_job *)malloc(sizeof(t_job))))
		return (0);
	j->p = p;
	j->pgid = pgid;
	j->next = 0;
	return (j);
}
void delete_job(pid_t pgid)
{
	t_job *j;
	t_job *prev;

	j = g_first_job;
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
			g_first_job = j->next;
		}
		free_job(j);
	}
}

t_job			*add_jobs(t_proc *p, pid_t pgid)
{
	t_job	*temp;

	if (g_first_job)
	{
		temp = g_first_job;
		while (temp->next)
			temp = temp->next;
		return ((temp->next = add_job(p, pgid)));
	}
	return ((g_first_job = add_job(p, pgid)));
}

void			free_job(t_job *j)
{
	free_process(j->p);
	ft_memdel((void**)&j);
}

void			free_jobs(void)
{
	t_job	*tp;

	while (g_first_job)
	{
		tp = g_first_job->next;
		free_process(g_first_job->p);
		ft_memdel((void**)&g_first_job);
		g_first_job = tp;
	}
	g_first_job = 0;
}
