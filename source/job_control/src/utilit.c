/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:25:32 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/15 11:25:40 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"


/*
** Mark a stopped job J as being running again. 
*/
void  mark_job_as_running (t_job *j)
{
  t_proc *p;

  p = j->p;
  while (p)
  {
    p->s = 0;
    p = p->next;
  }
  j->notified = 0;
}

/*
** Continue the job J.
*/
void  continue_job(t_job *j, int foreground)
{
  mark_job_as_running (j);
  if (foreground)
    put_job_in_foreground (j, 1);
  else
    put_job_in_background (j, 1);
}

/* 
**Find the active job with the indicated pgid.
*/
t_job       *find_job(pid_t pgid)
{
    t_job *j;

    j = g_jobs.f_job;
    while (j)
    {
        if (j->pgid == pgid)
            return (j);
        j = j->next;
    }
  return (NULL);
}

/* 
** Return true if all processes in the job have stopped or completed.
*/
int     job_is_stopped (t_job *j)
{
  t_proc *p;

  p = j->p;
  while (p)
  {
      if (!p->c && !p->s)
      return (0);
      p = p->next;
  }
  return (1);
}

/* Return true if all processes in the job have completed.  */
int     job_is_completed (t_job *j)
{
  t_proc *p;

  p = j->p;

  while (p)
  {
      if (!p->c)
        return (0);
    p = p->next;
  }
  return 1;
}