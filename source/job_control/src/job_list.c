/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 01:41:09 by hastid            #+#    #+#             */
/*   Updated: 2020/02/24 05:22:29 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

void		job_sign(t_job *j)
{
	t_job *tmp;
	int len;
	// int i;

	tmp = g_jobs.f_job;
	len = 0;
	// printf("-> last : %d \n",j->pgid);
	while(tmp)
		{
				// printf("%d , %d\n",j->pgid, tmp->pgid);
			if (tmp->sign == '-' && (j->sign != '+' ))
				tmp->sign = ' ';
			if (tmp->sign == '+' )
			{
				tmp->sign = '-';
				// break;
			}
			len++;
			tmp = tmp->next;
		}
	j->sign = '+';
	// if ( len >= 2)
	// {
	// 	j->sign = '+';
	// 	tmp = g_jobs.f_job;
	// 	i = 0;
	// 	while(i < len - 2)
	// 	{
	// 		i++;
	// 		tmp = tmp->next;
	// 	}
	// 	tmp->sign = ' ';
	// 	tmp->next->sign = '-';
	// }
	// else
	// 	j->sign = '+';
	
	
}

static t_job	*add_job(t_proc *p, pid_t pgid, int bg)
{
	t_job	*j;

	if (!(j = (t_job *)malloc(sizeof(t_job))))
		return (0);
	j->p = p;
	j->pgid = pgid;
	j->notified = 1;
	j->name = name_list_concate(p); // added here by noureddine
	j->cmd = p->as ? ft_strdup(p->as->token) : ft_strdup(p->red->token); // added by noureddine
	j->sign = 0; // important for later verifications
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
	ft_strdel(&j->name);
	ft_strdel(&j->cmd);
	ft_memdel((void**)&j);
}

void			free_jobs(void)
{
	t_job	*tp;
	t_job	*tmp;
	
	tp = g_jobs.f_job;
	while (tp)
	{
		tmp = tp;
		tp = tp->next;
		free_job(tmp);
	}
	g_jobs.f_job = 0;
}
