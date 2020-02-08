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

int				add_jobs(t_proc *p, pid_t pgid)
{
	t_job	*temp;

	if (g_first_job)
	{
		temp = g_first_job;
		while (temp->next)
			temp = temp->next;
		if (!(temp->next = add_job(p, pgid)))
			return (1);
	}
	else if (!(g_first_job = add_job(p, pgid)))
		return (1);
	return (0);
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
