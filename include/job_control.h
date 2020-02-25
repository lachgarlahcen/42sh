/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:18:48 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/25 06:16:24 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include "shell.h"
# include <unistd.h>
# include <termios.h>
# include <sys/types.h>
# include "struct_shell.h"

pid_t		g_shell_pgid;
t_jobs		g_jobs;

struct termios g_shell_tmodes;

t_job			*add_jobs(t_proc *p, pid_t pgid, int bg);

void			free_jobs(void);
int				job_is_stopped (t_job *j);
int				job_is_completed (t_job *j);
void			update_status (void);
void			put_job_in_foreground (t_job *j, int cont);
void			put_job_in_background (t_job *j, int cont);
t_job			*find_job(pid_t pgid);
void			wait_for_job (t_job *j);
void			do_job_notification (void);
void			format_job_info (t_job *j, char option);
void			free_job(t_job *j);
void			delete_job(pid_t pgid);
int				execute_jobs(char **args);
int				execute_fg(char **args);
int				execute_bg(char **args);
char			*name_list_concate(t_proc *p, char *name_args,
				char *tmp, t_tok *ptr);
void			job_sign(t_job *j);
void			mark_process(t_proc *p, int status);
int				mark_process_status(pid_t pid, int status);
void			printf_job_info(t_job *j, char *status, char opt);
int				ft_isdigits(char *str);
void			job_node_trait(t_job *j, int mines);
void			job_printing(char option);
t_job			*jobs_plus_ret(t_job *j);
t_job			*job_sign_finder(char sign);
void			job_node_manpl_signs(t_job *tmp, t_job *j);
void			job_node_trait(t_job *j, int mines);
int				check_ctr_jobs_args(char **args, t_job **j,char *str, int percent);
int				execute_bg(char **args);
int				execute_fg(char **args);
int				execute_jobs(char **args);
int				job_arg(char **args, char *option, int i);
int				job_arg_option(char *option, char **args);


#endif
