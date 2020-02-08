/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 05:14:50 by hastid            #+#    #+#             */
/*   Updated: 2020/02/08 01:39:55 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

void		check_save_tokens(t_proc *p, char *token, int id)
{
	while (p && p->next)
		p = p->next;
	if (id == 0)
		save_tokens(&(p->as), token, id);
	else
		save_tokens(&(p->red), token, id);
}

char		**get_args(t_tok *as)
{
	int		l;
	t_tok	*tmp;
	char	**args;

	l = 0;
	tmp = as;
	while (tmp)
	{
		l++;
		tmp =  tmp->next;
	}
	if (!(args = (char **)malloc(sizeof(char *) * (l + 1))))
		return (0);
	l = 0;
	tmp = as;
	while (tmp)
	{
		args[l++] = ft_strdup(tmp->token);
		tmp = tmp->next;
	}
	args[l] = 0;
	return (args);
}

char		*search_executable(char *cmdl)
{
	char	*excu;

	excu = ft_strjoin("/bin/", cmdl);
	if (!access(excu, F_OK))
		return (excu);
	ft_memdel((void **)&excu);
	ft_putendl_fd("command not found", 2);
	return (0);
}

int			launch_process(t_tok *as, int bg, int in, int out)
{
	char	*exec;
	char	**env;
	char	**args;

	if (!as)
		exit (0);
	bg = 0;
	if (!(exec = search_executable(as->token)))
		exit (EXIT_FAILURE);
	args =  get_args(as);
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
	execve(exec, args, env);
	exit (0);
}

void		wait_for_process(t_proc *p)
{
	int	status;

	while (p)
	{
		waitpid(p->pid, &status, WUNTRACED | WCONTINUED);
		p->stat = status;
		if (WIFSTOPPED (status))
			p->s = 1;
		else
			p->c = 1;
		p = p->next;
	}
}

int			execute_pipes_line(t_proc *p, int bg)
{
	int		in;
	int		out;
	int		pi[2];
	t_proc	*tp;

	in = 0;
	tp = p;
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
			signals(0);
			if (tp->next)
				close(pi[0]);
			launch_process(tp->as, bg, in, out);
		}
		if (in != 0)
			close (in);
		if (out != 1)
			close (out);
		in = pi[0];
		tp = tp->next;
	}
	wait_for_process(p);
	return (0);
}

void		separat_cmdl(t_tok *t)
{
	int		check;
	t_proc	*p;

	check = 0;
	while (t)
	{
		p = 0;
		while (t && t->id < 5)
		{
			add_process(&p);
			while (t && t->id < 4)
			{
				check_save_tokens(p, t->token, t->id);
				t = t->next;
			}
			if (t && t->id == 4)
				t = t->next;
		}
		(t && t->id == 5) ? execute_pipes_line(p, 1) : execute_pipes_line(p, 0);
		while (p)
		{
			printf("pid == %i\n", p->pid);
			if (WIFEXITED(p->stat)) {
				printf("exited, status = %d\n", WEXITSTATUS(p->stat));
			} else if (WIFSIGNALED(p->stat)) {
				printf("killed by signal %d\n", WTERMSIG(p->stat));
			} else if (WIFSTOPPED(p->stat)) {
				printf("stopped by signal %d\n", WSTOPSIG(p->stat));
			} else if (WIFCONTINUED(p->stat)) {
				printf("continued\n");
			}
			p = p->next;
		}
		free_process(p);
		if (t)
			t = t->next;
	}
}

int			execute_cmdline(char *line)
{
	t_tok	*t;

	t = parse_tokens(line);
	separat_cmdl(t);
	free_toks(t);
	return (0);
}
