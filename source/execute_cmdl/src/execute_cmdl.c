/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 05:14:50 by hastid            #+#    #+#             */
/*   Updated: 2020/02/15 13:10:35 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

int		check_dollar(char *str)
{
	int	i;
	int	be;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			be = i++;
			while (str[i] && str[i] != str[be])
			{
				if (str[i] == '$' && str[be] == '\"')
					return (1);
				i++;
			}
		}
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

char	*change_tilda(char *str)
{
	char	*tp;
	char	*tmp;

	tmp = 0;
	if (str[1] == '\0' || str[1] == '/')
	{
		if (!(tp = get_variable("HOME")))
			return (0); // err  HOME not set
		tmp = ft_strjoin(tp, str + 1);
		ft_memdel((void **)&tp);
		ft_memdel((void **)&str);
	}
	else
	{
		tmp = ft_strjoin("/Users/", str + 1);
		if (access(tmp, F_OK))
		{
			ft_memdel((void **)&tmp);
			tmp = str;
		}
		else
			ft_memdel((void **)&str);
	}
	return (tmp);
}

int		change_expansion(t_tok *t)
{
	while (t)
	{
		if (t->token && t->token[0] == '~')
			if (!(t->token = change_tilda(t->token)))
				return (1);
		/*if (check_dollar(t->token))
			t->token = change_dollar(t->token, t->id);*/
		t = t->next;
	}
	return (0);
}

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
	excu = ft_strjoin("/usr/bin/", cmdl);
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
	if (!execute_builtin(args))
		exit (0);
	if (!(exec = search_executable(as->token)))
		exit (EXIT_FAILURE);
	env = get_env_variables();
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
				p->c = 0;
				p->s = 0;
				t = t->next;
			}
			if (t && t->id == 4)
				t = t->next;
		}
		(t && t->id == 5) ? execute_pipes_line(p, 1) : execute_pipes_line(p, 0);
		/*		while (p)
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
				*/		//free_process(p);
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
