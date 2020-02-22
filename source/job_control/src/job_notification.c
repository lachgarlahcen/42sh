/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_notification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 00:42:10 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/23 00:02:02 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

/*
 ** Store the status of the process pid that was returned by waitpid.
 ** Return 0 if all went well, nonzero otherwise.
 */

int mark_process_status (pid_t pid, int status)
{
	t_job *j;
	t_proc *p;
	j = g_jobs.f_job;

	if (pid > 0)
	{
		/* 
		 **Update the record for the process.
		 */
		while (j)
		{
			p = j->p;
			while (p)
			{
				if (p->pid == pid)
				{
					p->stat = status;
					if (WIFSTOPPED (status))
					{
						p->s = 1;
						j->status = WSTOPSIG(status);
					}

					else
					{
						p->c = 1;
						j->notified = 0;
						if (WIFSIGNALED(p->stat))
							j->status = WTERMSIG(status);
						else
							j->status = WEXITSTATUS(status);
					}
					// printf("status 111 -> %d\n",j->status);
					return 0;
				}
				p = p->next;
			}
	// printf("status 222 -> %d\n",j->status);
			j = j->next;
		}
	}
	return (1);
}

void  update_status (void)
{
	int status;
	pid_t pid;
	//t_job *j;

	// j = g_jobs.f_job;
	// while (j)
	// {
	//   ft_printf("pgid%d\n", j->pgid);
	//   j = j->next;
	// }
	do
		pid = waitpid (WAIT_ANY, &status, WUNTRACED|WNOHANG);
	while (!mark_process_status(pid, status));
}

void  wait_for_job (t_job *j)
{
	int status;
	pid_t pid;
	t_proc	*p;

	while (1)
	{
		pid = waitpid (WAIT_ANY, &status, WUNTRACED);
		if (mark_process_status (pid, status))
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
		exit_status(WTERMSIG(p->stat) + 128, 1);
	else if (WIFSTOPPED(j->status))
		exit_status(WSTOPSIG(p->stat) + 128, 1);
}


void  format_job_info (t_job *j, const char *status, char option)
{
	char *g_sinalmsg[] =
	{
		"Done",
		"Hangup",                                                                                                                                                                                                                                         
		"Interrupt",                                                                                                                                                                                                                                      
		"Quit",                                                                                                                                                                                                  
		"Illegal instruction",                                                                                                                                                                                                                            
		"Trace/breakpoint trap",                                                                                                                                                                                                                          
		"Aborted",                                                                                                                                                                                                                                       
		"Bus error",                                                                                                                                                                                                                                      
		"Floating point exception",                                                                                                                                                                                                                       
		"Killed",                                                                                                                                                                                                                                         
		"User defined signal 1",                                                                                                                                                                                                                          
		"Segmentation fault",                                                                                                                                                                                                                             
		"User defined signal 2",                                                                                                                                                                                                                          
		"Broken pipe",                                                                                                                                                                                                                                    
		"Alarm clock",                                                                                                                                                                                                                                    
		"Terminated",                                                                                                                                                                                                                                     
		"Stack fault",                                                                                                                                                                                                                                    
		"Child exited",                                                                                                                                                                                                                                   
		"Continued",                                                                                                                                                                                                                                      
		"Stopped (signal)",                                                                                                                                                                                                                               
		"Stopped",                                                                                                                                                                                                                                        
		"Stopped (tty input)",                                                                                                                                                                                                                            
		"Stopped (tty output)",                                                                                                                                                                                                                           
		"Urgent I/O condition",                                                                                                                                                                                                                           
		"CPU time limit exceeded",                                                                                                                                                                                                                        
		"File size limit exceeded",                                                                                                                                                                                                                       
		"Virtual timer expired",                                                                                                                                                                                                                          
		"Profiling timer expired",                                                                                                                                                                                                                        
		"Window changed",                                                                                                                                                                                                                                 
		"I/O possible",                                                                                                                                                                                                                                   
		"Power failure"
	};
	(void )status;
	int s;

	s = j->status;
	if (option == 0)
		fprintf (stderr, "[%d]%c %s\t\t%s\n",j->id , j->sign, g_sinalmsg[s], j->name);
	else if (option == 'l')
	{
		fprintf (stderr, "[%d]%c  %ld  %s\t\t%s\n",j->id , j->sign, (long)j->pgid, g_sinalmsg[s], j->name);
	}
	else if(option == 'p')
		fprintf (stderr, "%d\n",j->pgid);
	else
		fprintf(stderr, "jobs: -%c: invalid option\nusage: jobs [-lp] [jobspec ...]\n",option);



}
void  do_job_notification (void)
{
	t_job *j, *jlast, *jnext;
	//t_proc *p;

	/* Update status information for child processes.  */
	update_status ();

	jlast = NULL;
	for (j = g_jobs.f_job; j; j = jnext)
	{
		jnext = j->next;

		/* If all processes have completed, tell the user the job has
		   completed and delete it from the list of active jobs.  */
		if (job_is_completed (j)) {
			format_job_info (j, "completed", 0);
			if (jlast)
				jlast->next = jnext;
			else
				g_jobs.f_job = jnext;
			free_job (j);
		}

		/* Notify the user about stopped jobs,
		   marking them so that we won’t do this more than once.  */
		else if (job_is_stopped (j) && !j->notified) {
			format_job_info (j, "stopped", 0);
			j->notified = 1;
			jlast = j;
		}

		/* Don’t say anything about jobs that are still running.  */
		else
			jlast = j;
	}
}
