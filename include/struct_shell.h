/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_shell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 23:54:11 by hastid            #+#    #+#             */
/*   Updated: 2020/02/18 23:54:12 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_SHELL_H
# define STRUCT_SHELL_H

typedef struct	s_tok
{
	int				id;
	char			*token;
	struct s_tok	*next;
}				t_tok;

typedef struct	s_var
{
	int				id;
	char			*name;
	char			*value;
	struct s_var	*next;
}				t_var;

typedef struct	s_proc
{
	pid_t			pid;
	int				stat;
	t_tok			*as;
	t_tok			*red;
	char			s;
	char			c;
	struct s_proc	*next;
}				t_proc;

typedef struct	s_job
{
	t_proc			*p;
	int				id;
	int				status;
	pid_t			pgid;
	char			notified; 
	struct s_job	*next;
	char			option;
	char			*name;
}				t_job;

typedef struct s_jobs
{
	struct  s_job *f_job;
	int 			p;
	int				id;
	
}				t_jobs;


#endif
