/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 05:14:50 by hastid            #+#    #+#             */
/*   Updated: 2020/02/13 00:11:28 by hastid           ###   ########.fr       */
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

char	*change_string(char *str, int be)
{
	int		i;
	char	*tp;
	char	*tmp;

	i = be;
	tp = 0;
	if (str[be] == '{')
	{
		while (str[i] && str[i] != '}')
			i++;
		be++;
	}
	else
		while (str[i] && ft_isalnum(str[i]) && str[i] != '_')
			i++;
	tp = ft_strsub(str, be, i - be);
	if (!ft_strcmp("?", tp))
		tmp = ft_itoa(exit_status(0, 0));
	else
		tmp = get_variable(tp);
	ft_memdel((void **)&tp);
	tp = ft_strsub(str, 0, (str[be - 1] == '{') ? be - 2 : be - 1);
	if (tmp)
		tp = strjoin_free(tp, tmp, 1, 1);
	if (str[i] == '}')
		i++;
	tmp = ft_strsub(str, i, ft_strlen(str) - i);
	tp = strjoin_free(tp, tmp, 1, 1);
	if (!*tp)
		ft_memdel((void **)&tp);
	return (tp);
}

char	*change_dollar(char *str, int id)
{
	int		i;
	int		be;
	//	char	*tp;
	char	*tmp;

	i = 0;
	tmp = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			be = i++;
			while (str[i] && str[i] != str[be])
			{
				if (str[i] == '$' && str[be] == '\"')
					return (0);
				i++;
			}
		}
		if (str[i] == '$')
			tmp = change_string(str, i + 1);
		i++;
	}
	if (!tmp && id != 0)
		return (str);
	ft_memdel((void **)&str);
	return (tmp);
}

int		change_expansion(t_tok *t)
{
	while (t)
	{
		if (t->token && t->token[0] == '~')
			if (!(t->token = change_tilda(t->token)))
				return (1);
		if (check_dollar(t->token))
			t->token = change_dollar(t->token, t->id);
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
		if (tmp->token)
			l++;
		tmp =  tmp->next;
	}
	if (!(args = (char **)malloc(sizeof(char *) * (l + 1))))
		return (0);
	l = 0;
	tmp = as;
	while (tmp)
	{
		if (tmp->token)
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
		printf("pid == %i\n", p->pid);
		if (WIFEXITED(p->stat))
			exit_status(WEXITSTATUS(p->stat), 1);
		else if (WIFSIGNALED(p->stat))
			exit_status(WTERMSIG(p->stat) + 128, 1);
		else if (WIFSTOPPED(p->stat))
			exit_status(WSTOPSIG(p->stat) + 128, 1);
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
//	wait_for_process(p);
	j = add_jobs(p, pgid);
	if (bg)
	{
		put_job_in_background(j, 0);
		ft_printf("[1] %ld\n", j->pgid);
		job_is_completed(j);
	}
	else
	{
		put_job_in_foreground(j, 0);
		if (job_is_completed(j))
			delete_job(j->pgid);
		// tcsetpgrp (STDIN_FILENO, pgid);
		// wait_for_process(p);
		// tcsetpgrp (STDIN_FILENO, g_shell_pgid);
	}
	do_job_notification();
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
		//free_process(p);
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
