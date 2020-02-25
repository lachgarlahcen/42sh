/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:16:28 by hastid            #+#    #+#             */
/*   Updated: 2020/02/25 04:36:11 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

static int	execute_args(t_tok *as, char **args)
{
	char	*exec;
	char	**env;

	while (as && as->id)
	{
		set_variable(as->token, 1, 1);
		as = as->next;
	}
	if (is_builtin(args[0]))
		exit(execute_builtin(args));
	if (!(exec = search_executable(as->token)))
		exit(1);
	env = get_env_variables();
	free_temp_variables();
	if (execve(exec, args, env) == -1)
		ft_perror_pipe("EXECVE ERROR !!", 1);
	exit(1);
	return (0);
}

static int	launch_process(t_proc *p, char **args, int in, int out)
{
	signals(0);
	if (in != 0)
	{
		if (dup2(in, 0) == -1)
			exit(1);
		close(in);
	}
	if (out != 1)
	{
		if (dup2(out, 1) == -1)
			exit(1);
		close(out);
	}
	if (p->red)
		if (ft_redirection(p) == 1)
			exit(1);
	if (!p->as)
		exit(0);
	execute_args(p->as, args);
	return (0);
}

static int	execute_pipe(t_proc *p, int *in)
{
	int		out;
	int		pi[2];
	char	**args;

	out = 1;
	if (p->next)
	{
		if (pipe(pi) == -1)
			return (ft_perror_pipe("PIPE ERROR !!", 1));
		out = pi[1];
	}
	if ((p->pid = fork()) == -1)
		return (ft_perror_pipe("PIPE ERROR !!", 1));
	args = get_args(p->as);
	if (p->pid == 0)
	{
		if (p->next)
			close(pi[0]);
		launch_process(p, args, *in, out);
	}
	(*in != 0) ? close(*in) : 0;
	(out != 1) ? close(out) : 0;
	*in = pi[0];
	free_tab(args);
	return (0);
}

int			execute_pipes_line(t_proc *p, int bg)
{
	int		in;
	int		pgid;
	t_job	*j;
	t_proc	*tp;

	in = 0;
	tp = p;
	pgid = 0;
	while (tp)
	{
		if (execute_pipe(tp, &in))
			break ;
		if (!pgid)
			pgid = p->pid;
		setpgid(p->pid, pgid);
		tp = tp->next;
	}
	j = add_jobs(p, pgid, bg);
	if (bg)
		job_sign(j);
	bg ? put_job_in_background(j, 0) : put_job_in_foreground(j, 0);
	return (0);
}

int			execute_without_fork(t_proc *p, int iv)
{
	t_tok	*as;
	char	**args;

	if (p->red)
		if (ft_redirection(p))
			return (exit_status(1, 1));
	as = p->as;
	if (iv)
		return (set_intern_variables(as));
	while (as && as->id)
	{
		set_variable(as->token, 1, 1);
		as = as->next;
	}
	args = get_args(as);
	exit_status(execute_builtin(args), 1);
	if (init_fd(0))
		exit(1);
	free_temp_variables();
	free_tab(args);
	return (0);
}
