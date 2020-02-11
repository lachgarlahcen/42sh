/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:18:53 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/08 00:31:28 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

void  put_job_in_foreground (t_job *j, int cont)
{
  /* Put the job into the foreground.  */
  tcsetpgrp (STDIN_FILENO, j->pgid);

  /* Send the job a continue signal, if necessary.  */
  if (cont)
    {
      //tcsetattr (shell_terminal, TCSADRAIN, &j->tmodes);
      if (kill (- j->pgid, SIGCONT) < 0)
        perror ("kill (SIGCONT)");
    }

  /* Wait for it to report.  */
  wait_for_job (j);

  /* Put the shell back in the foreground.  */
  tcsetpgrp (STDIN_FILENO, g_shell_pgid);
  tcsetattr (STDIN_FILENO, TCSADRAIN, &g_shell_tmodes);
}

/*
** this function is basctly puts a jib in the background 
** it it is supanded it sends continue sig
** and it not gave it the control to be and the forground
*/
void  put_job_in_background (t_job *j, int cont)
{
  /* Send the job a continue signal, if necessary.  */
  if (cont)
    kill (- j->pgid, SIGCONT);
}