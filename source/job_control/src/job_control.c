/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:18:53 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/20 06:47:24 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

void		job_sign(t_job *j);
char *name_list_concate(t_proc *p)
{
  char *name_args;
  char *tmp;
  t_tok *ptr;

  ptr = p->as;
  if (ptr->next)
    name_args = ptr->token;
  else
    name_args = ft_strdup(ptr->token);
  /*
    * function : for concatinate the name of processe
    *     for free purpeses 
    *      any return from 
    * this fuction is allocated
    */
  while (ptr->next)
  {
    tmp = ft_strjoin(name_args, " ");
    ptr = ptr->next;
    name_args = ft_strjoin(tmp, ptr->token);
    free(tmp);
  }
  return (name_args);
}

void job_printing(char option)
{
  t_job *j;
  j = g_jobs.f_job;
  while (j)
  {
    j->notified = 1;
    format_job_info(j, NULL, option);
    j = j->next;
    if (!(option == 'l' || option == 'p' || option == 0)) // if not one of the fuctions break;
      break;
  }
}

int ft_isdigits(char *str)
{
  if (str)
  {
    if (*str == '%')
      str++;
    while (*str)
    {
      if (ft_isdigit(*str))
        str++;
      else
        return (0);
    }
    return (1);
  }
  return (0);
}

void execute_jobs(char **args)
{
  t_job *j;
  (void)args;
  int i;
  static char option = 0; // for recursive to conserve value

  i = 0;
  j = g_jobs.f_job;
  if (args[1] && args[1][0] == '-')
  {
    while (args[1][++i])
    {
      option = args[1][i];
      if (!(args[1][i] == 'l' || args[1][i] == 'p'))
      {
        option = args[1][i];
        break;
      }
    }
    if (args[2])
    {
      execute_jobs(args + 1);
      option = 0; // restore value for the other cmd $>jobs
      return;
    }
    job_printing(option);
  }
  else if (args[1]) // looking for jobs args :  jobs CMD_NAME
  {
    t_job *jj;
    jj = j;
    int percent;

    args[1][0] == '%' ? percent = 1 : 0;
    int i = 1;
    while (j)
    {
      if (args[i] && (ft_strequ(args[i], j->cmd) || (ft_isdigits(args[i]) && ft_atoi(args[i] + percent) == j->id)))
      {
        i++;
        format_job_info(j, NULL, option);
        j = jj;
      }
      else
        j = j->next;
      if (!j && args[i])
      {
        fprintf(stderr, "jobs: job not found: %s\n", args[i]);
        break;
      }
    }
  }
  else // cmd  : |$>jobs|
    job_printing(option);
  option = 0; // restore value for the other cmd $>jobs -[...]
}

void execute_fg(char **args)
{
    t_job   *j;

  (void)args;
  j = g_jobs.f_job;
  if (args[1] && ft_isdigits(args[1])) // fg [job_id]
  {
    while(j)
    {
      if (j->id == ft_atoi(args[1]))
        break;
      j = j->next;
    }
  }
  else if (args[1]) // error msgs
  {
    printf("42sh : fd: %s no such job\n",args[1]);
    return ;
  }
  else // fg to to  +
  {
    while(j)
    {
      if (j->sign == '+')
        break;
      j = j->next;
    }
  }
  
  if (getpid() != g_shell_pgid)
    ft_printf("fg: no job control\n");
  put_job_in_foreground(j, 1);
  job_sign(j); // added by noureddine
  
}

void execute_bg(char **args)
{
  (void)args;
  put_job_in_background(g_jobs.f_job, 1);
}

void put_job_in_foreground(t_job *j, int cont)
{
  /* Put the job into the foreground.  */ // give permission to write on terminal
  tcsetpgrp(STDIN_FILENO, j->pgid);
  /* Send the job a continue signal, if necessary.  */
  if (cont)
  {
    //tcsetattr (shell_terminal, TCSADRAIN, &j->tmodes);
    if (killpg(j->pgid, SIGCONT) < 0)
      perror("kill (SIGCONT)");
  }
  /*
  ** Wait for it to report.
  */
  wait_for_job(j);
  /* 
  ** Put the shell back in the foreground.
  */
  tcsetpgrp(STDIN_FILENO, g_shell_pgid);
  tcsetattr(STDIN_FILENO, TCSADRAIN, &g_shell_tmodes);
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
void put_job_in_background(t_job *j, int cont)
{
  /* 
  **Send the job a continue signal, if necessary.
  */
  if (cont)
    killpg(j->pgid, SIGCONT);
  else
    ft_printf("[%d] %ld\n", j->id, j->pgid);
}