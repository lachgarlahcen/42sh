/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 12:16:28 by hastid            #+#    #+#             */
/*   Updated: 2020/02/23 01:12:24 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

int			ft_perror_pipe(char *error, int ret)
{
	ft_putstr_fd("42sh: ", 2);
	ft_putendl_fd(error, 2);
	return (ret);
}

int			is_dir(char *di)
{
	DIR	*d;
	if (!(d = opendir(di)))
		return (0);
	closedir(d);
	return (1);
}

int			ft_perror_execu(char *cmdl, char *err)
{
	ft_putstr_fd("42sh : ", 2);
	ft_putstr_fd(cmdl, 2);
	ft_putendl_fd(err, 2);
	return (1);
}

char		*search_executable(char *cmdl)
{
	char	*excu;

	cmdl = delet_quotes(cmdl);
	if (!access(cmdl, F_OK))
		if (!access(cmdl, X_OK))
			if (!is_dir(cmdl))
				return (cmdl);
	if (!is_dir(cmdl))
	{
		excu = is_binary(cmdl);
		/*		excu = ft_strjoin("/bin/", cmdl);
				if (!access(excu, F_OK))
				return (excu);
				ft_memdel((void **)&excu);
				excu = ft_strjoin("/usr/bin/", cmdl);
				if (!access(excu, F_OK))
				return (excu);
				ft_memdel((void **)&excu);
				*/
		if (excu)
			return (excu);
		else if ((excu = get_bin_path(cmdl)))
			return (excu);
		ft_perror_execu(cmdl, ": command not found");
	}
	else
		ft_perror_execu(cmdl, ": is a directory");
	return (0);
}

int			execute_args(t_tok *as, char **args)
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
		exit (1);
	env = get_env_variables();
	if (execve(exec, args, env) == -1)
		ft_perror_pipe("EXECVE ERROR !!", 1);
	exit (1);
	return (0);
}

int			launch_process(t_proc *p, char **args, int in, int out)
{
	signals(0);
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
	if (p->red)
		if (ft_redirection(p) == 1)
			exit (1);
	if (!p->as)
		exit (0);
	execute_args(p->as, args);
	return (0);
}

int			execute_pipe(t_proc *p, int *in, int *pgid)
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
	if (change_expansion(p->as) || change_expansion(p->red))
		return (exit_status(1, 0));
	args = get_args(p->as);
	if (p->pid == 0)
	{
		if (p->next)
			close(pi[0]);
		launch_process(p, args, *in, out);
	}
	if (!*pgid)
		*pgid = p->pid;
	setpgid(p->pid, *pgid);
	if (*in != 0)
		close (*in);
	if (out != 1)
		close (out);
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
		if (execute_pipe(tp, &in, &pgid))
			break ;
		tp = tp->next;
	}
	j = add_jobs(p, pgid, bg);
	if (bg)
	{
		printf("job_sign called for bg\n");
		job_sign(j); // added by noureddine
		put_job_in_background(j, 0);
	}
	else
		put_job_in_foreground(j, 0);
	return (0);
}

int		execute_without_fork(t_proc *p, int iv)
{
	t_tok	*as;
	char	**args;

	if (p->red)
		if (change_expansion(p->red) || ft_redirection(p))
			return (exit_status(1, 1));
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
	if (init_fd(0))
		exit(1);
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
