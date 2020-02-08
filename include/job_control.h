/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:18:48 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/08 03:11:13 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
# define JOB_CONTROL_H

# include "shell.h"
# include <unistd.h>
# include <termios.h>
# include <sys/types.h>

t_job		*g_first_job;

int			add_jobs(t_proc *p, pid_t pgid);

void		free_jobs(void);

#endif

