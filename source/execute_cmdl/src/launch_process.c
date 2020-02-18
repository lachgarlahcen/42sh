/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 04:57:40 by hastid            #+#    #+#             */
/*   Updated: 2020/02/18 06:32:12 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

char		*search_executable(char *cmdl)
{
	char	*excu;

	excu = ft_strjoin("/bin/", cmdl);
	if (!access(excu, F_OK))
		return (excu);
	ft_memdel((void **)&excu);
	excu = ft_strjoin("/usr/bin/", cmdl);
	if (!access(excu, F_OK))
		return (excu);
	ft_memdel((void **)&excu);
	ft_putstr_fd(cmdl, 2);
	ft_putendl_fd(" :command not found", 2);
	return (0);
}

int			launch_process(t_tok *as, int bg, int in, int out)
{
	int		ret;
	char	*exec;
	char	**env;
	char	**args;

	if (!as)
		exit (0);
	if (in != 0)
	{
		if (dup2(in, 0) == -1)
			exit (1);
		close (in);
	}
	if (out != 1)
	{
		if (dup2 (out, 1) == -1)
			exit (1);
		close (out);
	}
	signals(0);
	bg = 0;
	args =  get_args(as);
	if (is_builtin(args[0]))
	{
		ret = execute_builtin(args);
		exit (ret);
	}
	if (!(exec = search_executable(as->token)))
		exit (EXIT_FAILURE);
	env = get_env_variables();
	execve(exec, args, env);
	exit (0);
}

int			execute_pipes_line(t_proc *p, int bg)
{
	int		in;
	int		out;
	int		pgid;
	int		pi[2];
	t_proc	*tp;
	t_job	*j;

	in = 0;
	tp = p;
	pgid = 0;
	while (tp)
	{
		if (tp->next)
		{
			if (pipe(pi) == -1)
				return (1); //				ft_putendl("pipe failed !!");
			out = pi[1];
		}
		else
			out = 1;
		if ((tp->pid = fork()) == -1)
			return (1); //				ft_putendl("fork failed !!");
		if (tp->pid == 0)
		{
			if (tp->next)
				close(pi[0]);
			if (!change_expansion(tp->as))
				launch_process(tp->as, bg, in, out);
			exit(1);
		}
		if (!pgid)
			pgid = tp->pid;
		setpgid(tp->pid, pgid);
		if (in != 0)
			close (in);
		if (out != 1)
			close (out);
		in = pi[0];
		tp = tp->next;
	}
	j = add_jobs(p, pgid, bg);
	if (bg)
		put_job_in_background(j, 0);
	else
		put_job_in_foreground(j, 0);
	return (0);
}

int		execute_without_fork(t_proc *p, int iv)
{
	t_tok	*as;
	char	**args;

//	if (p->red)
//		redirect(p->red);
	if (!(as = p->as))
		return (0);
	if (iv)
	{
		while (as)
		{
			set_variable(as->token, 0, 0);
			as = as->next;
		}
		return (exit_status(0, 1));
	}
	while (as && as->id)
	{
		set_variable(as->token, 1, 1);
		as = as->next;
	}
	if (change_expansion(as))
		return (exit_status(1, 1));
	args = get_args(as);
	exit_status(execute_builtin(args), 1);
	free_tab(args);
	return (0);
}

int			check_fork(t_proc *p, int bg)
{
	int		iv;
	t_tok	*as;

	iv = 0;

	check_all_arguments(p);
	if (!p->next && !bg)
	{
		as = p->as;
		if (as && as->id)
			iv = 1;
		while (as && as->id)
			as = as->next;
		if (as)
			iv = 0;
		if (!as || is_builtin(as->token))
			return (execute_without_fork(p, iv));
	}
	return (execute_pipes_line(p, bg));
}
