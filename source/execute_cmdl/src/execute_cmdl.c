/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 05:14:50 by hastid            #+#    #+#             */
/*   Updated: 2020/02/06 05:40:04 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

void		check_save_tokens(t_pipe *p, char *token, int id)
{
	while (p && p->next)
		p = p->next;
	if (id == 0)
		save_tokens(&(p->as), token, id);
	else
		save_tokens(&(p->red), token, id);
}

int			launch_process(t_tok *args, int bg)
{
	ft_printf("%d -- background\n", bg);
	while (args)
	{
		ft_putendl(args->token);
		args = args->next;
	}
//	exit(0);
	return (1);
}

int			execute_pipes_line(t_pipe *p, int bg)
{
	int		in;
	int		out;
//	int		pid;
//	int		pi[2];

	in = 0;
	out = 1;
	while (p)
	{
/*		if (p->next)
			if (pipe(pi) == -1)
				return (1); //				ft_putendl("pipe failed !!");
*///		if ((pid = fork()) == -1)
//			return (1); //				ft_putendl("fork failed !!");
//		if (pid == 0)
			launch_process(p->as, bg);
/*		out = pi[1];
		if (in != 0)
			close (in);
		if (out != 1)
			close (in);
		in = pi[0];
*/		p = p->next;
	}
	return (0);
}

void		separat_cmdl(t_tok *t)
{
	int		check;
	t_pipe	*p;

	check = 0;
	while (t)
	{
		p = 0;
		while (t && t->id < 5)
		{
			add_pipes(&p);
			while (t && t->id < 4)
			{
				check_save_tokens(p, t->token, t->id);
				t = t->next;
			}
			if (t && t->id == 4)
				t = t->next;
		}
		(t && t->id == 5) ? execute_pipes_line(p, 1) : execute_pipes_line(p, 0);
		free_pipes(p);
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
