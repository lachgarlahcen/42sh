/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 05:14:50 by hastid            #+#    #+#             */
/*   Updated: 2020/02/06 04:43:33 by hastid           ###   ########.fr       */
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

void		execute_pipes_line(t_pipe *p, int bg)
{
	t_tok	*tp;

	ft_printf(" ---- %d\n", bg);
	while (p)
	{
		if (p->as)
		{
			tp = p->as;
			ft_printf("args    -----\n");
			while (tp)
			{
				ft_printf("|%d|  |%s|\n", tp->id, tp->token);
				tp = tp->next;
			}
		}
		if (p->red)
		{
			tp = p->red;
			ft_printf("redirection    -----\n");
			while (tp)
			{
				ft_printf("|%d|  |%s|\n", tp->id, tp->token);
				tp = tp->next;
			}
		}
		p = p->next;
	}
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
