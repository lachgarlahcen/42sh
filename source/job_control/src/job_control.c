/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:18:53 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/18 06:43:42 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

char  *name_list_concate(t_proc			*p)
{
    char *name_args;
    char *tmp;

    if (p->as->next)
      name_args = p->as->token;
    else
    name_args = ft_strdup(p->as->token); 
    /*
    *
    *     for free purpeses 
    *      any return from 
    * this fuction is allocated
    */
    while(p->as->next)
    {
        tmp = ft_strjoin(name_args, " ");
        p->as = p->as->next;
        name_args = ft_strjoin(tmp, p->as->token);
        free(tmp);
    }
    return(name_args);
}

void execute_jobs(char **args)
{
  t_job *j;
  (void )args;
  int i;
  int option;

  i = 0;
  j = g_jobs.f_job;
  option = 0;
  if (args[1] && args[1][0] == '-')
  {
      while(args[1][++i])
      {
        option = args[1][i];
        if (!(args[1][i] == 'l' || args[1][i] == 'p'))
        {
          option = 'x';
          break ;
        }
      }
  }
  /*
  
  */
  j = g_jobs.f_job;
  while (j)
  {
    j->notified = 1;
    j->option = option;
    j->name = name_list_concate(j->p); // must be freed later
   format_job_info(j, NULL);
    j = j->next;
  }
}

void execute_fg(char **args)
{
  (void )args;
  if (getpid() != g_shell_pgid)
    ft_printf("fg: no job control\n");
  put_job_in_foreground(g_jobs.f_job, 1);
}

void execute_bg(char **args)
{
  (void )args;
  put_job_in_background(g_jobs.f_job, 1);
}

void  put_job_in_foreground (t_job *j, int cont)
{
    /* Put the job into the foreground.  */
    tcsetpgrp (STDIN_FILENO, j->pgid);
  /* Send the job a continue signal, if necessary.  */
  if (cont)
    {
      //tcsetattr (shell_terminal, TCSADRAIN, &j->tmodes);
      if (killpg(j->pgid, SIGCONT) < 0)
        perror ("kill (SIGCONT)");
    }
  /*
  ** Wait for it to report.
  */
  wait_for_job (j);
  /* 
  ** Put the shell back in the foreground.
  */
  tcsetpgrp (STDIN_FILENO, g_shell_pgid);
  tcsetattr (STDIN_FILENO, TCSADRAIN, &g_shell_tmodes);
  if (job_is_completed(j))
  {
			delete_job(j->pgid);
  }
  else
    j->id = g_jobs.id++;
}
/*
** this function is basctly puts a jib in the background
** it it is supanded it sends continue sig
** and it not gave it the control to be and the forground
*/
void  put_job_in_background (t_job *j, int cont)
{
  /* 
  **Send the job a continue signal, if necessary.
  */
  if (cont)
    killpg(j->pgid, SIGCONT);
  else
    ft_printf("[%d] %ld\n",j->id, j->pgid);
}