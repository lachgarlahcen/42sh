/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:18:48 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/06 22:27:24 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOB_CONTROL_H
#define JOB_CONTROL_H
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

typedef struct s_process
{
  struct process *next;       /* next process in pipeline */
  char **argv;                /* for exec */
  pid_t pid;                  /* process ID */
  char completed;             /* true if process has completed */
  char stopped;               /* true if process has stopped */
  int status;                 /* reported status value */
} t_process;

/* A job is a pipeline of processes.  */
typedef struct s_job
{
  struct job *next;           /* next active job */
  char *command;              /* command line, used for messages */
  t_process *first_process;     /* list of processes in this job */
  pid_t pgid;                 /* process group ID */
  char notified;              /* true if user told about stopped job */
  struct termios tmode;      /* saved terminal modes */
  int stdin, stdout, stderr;  /* standard i/o channels */
} t_job;

t_job *g_first_job = NULL;


#endif

