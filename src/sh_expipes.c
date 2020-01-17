/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_expipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 03:31:09 by hastid            #+#    #+#             */
/*   Updated: 2019/12/19 14:36:03 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int		pipe_builtin(int inp, int pi[2], t_env **env, t_pipe *pipes)
{
	t_file	*fil;

	if (save_file(&fil, 0, 1, 2))
		return (1);
	if (inp)
		if (dup2(inp, 0) == -1)
			return (ft_perror(0, "duplicate input failed", 1));
	if (inp)
		close(inp);
	if (pipes->next)
		if (dup2(pi[1], 1) == -1)
			return (ft_perror(0, "duplicate input failed", 1));
	close(pi[1]);
	execute_builtins(pipes->tok, env);
	free_file(fil);
	return (0);
}

static int		child_process(t_tok *t, t_env **env)
{
	if (!duplicate(t))
		execute_tok(t, env);
	exit(1);
	return (0);
}

static int		pipe_cmdl(int inp, int pi[2], t_env **env, t_pipe *pipes)
{
	int		pid;
	int		ret;

	ret = 0;
	if ((pid = fork()) == -1)
		return (ft_perror(0, "fork failed", 1));
	if (pid == 0)
	{
		if (inp)
			if (dup2(inp, 0) == -1)
				ret = ft_perror(0, "duplicate input failed", 1);
		if (inp)
			close(inp);
		close(pi[0]);
		if (pipes->next)
			if (dup2(pi[1], 1) == -1)
				ret = ft_perror(0, "duplicate output failed", 1);
		close(pi[1]);
		if (ret || child_process(pipes->tok, env))
			exit(1);
	}
	return (0);
}

int				execute_pipe(int inp, int pi[2], t_env **env, t_pipe *pipes)
{
	t_tok	*tp;

	tp = pipes->tok;
	while (tp && tp->id != 0)
		tp = tp->next;
	if (!tp)
		return (0);
	if (check_built(tp->value))
		pipe_builtin(inp, pi, env, pipes);
	else if (pipe_cmdl(inp, pi, env, pipes))
	{
		if (inp)
			close(inp);
		close(pi[1]);
		return (1);
	}
	if (inp)
		close(inp);
	close(pi[1]);
	return (0);
}
