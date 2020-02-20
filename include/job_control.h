/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:18:48 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/20 11:50:43 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include "shell.h"
# include <unistd.h>
# include <termios.h>
# include <sys/types.h>
# include "struct_shell.h"

pid_t       g_shell_pgid;
t_jobs      g_jobs;


struct termios g_shell_tmodes;

t_job			*add_jobs(t_proc *p, pid_t pgid, int bg);

void		    free_jobs(void);
int             job_is_stopped (t_job *j);
int             job_is_completed (t_job *j);
void            update_status (void);
void            put_job_in_foreground (t_job *j, int cont);
void            put_job_in_background (t_job *j, int cont);
t_job           *find_job(pid_t pgid);
void            wait_for_job (t_job *j);
void            do_job_notification (void);
void            format_job_info (t_job *j, const char *status, char option);
void			free_job(t_job *j);
void            delete_job(pid_t pgid);
void            execute_jobs(char **args);
void            execute_fg(char **args);
void            execute_bg(char **args);
char            *name_list_concate(t_proc			*p);
void		    job_sign(t_job *j);

#endif

