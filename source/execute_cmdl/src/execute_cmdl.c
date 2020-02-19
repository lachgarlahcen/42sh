/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 05:14:50 by hastid            #+#    #+#             */
/*   Updated: 2020/02/19 02:23:27 by iel-bouh         ###   ########.fr       */
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

void		wait_for_process(t_proc *p)
{
	int	status;

	while (p)
	{
		waitpid(p->pid, &status, WUNTRACED | WCONTINUED);
		p->stat = status;
		if (WIFSTOPPED(status))
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

int			check_execute(t_proc *p, t_tok *t, int check)
{
	if (t && t->id == 5)
		return (check_fork(p, 1));
	/*	if (check == 1 && exit_status(0, 0))
		{
		free_process(p);
		return (check);
		}
		if (check == 2 && !exit_status(0, 0))
		{
			if (tp->next)
				close(pi[0]);
			if (ft_redirection(p) == 1)
				exit(1);
			if (!change_expansion(tp->as))
				launch_process(tp->as, bg, in, out);

			exit(1);
		}
		*/
	if (t && t->id == 7)
		check = !ft_strcmp("&&", t->token) ? 1 : 2;
	else
		check = 0;
	check_fork(p, 0);
	return (check);
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
		check = check_execute(p, t, check);
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
