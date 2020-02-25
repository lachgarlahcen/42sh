/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmdl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 03:40:43 by hastid            #+#    #+#             */
/*   Updated: 2020/02/25 04:33:13 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

static int	check_fork(t_proc *p, int bg)
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
		if (p->as)
			if (iv || is_builtin(as->token))
			{
				iv = execute_without_fork(p, iv);
				free_process(p);
				return (iv);
			}
	}
	return (execute_pipes_line(p, bg));
}

static void	check_save_tokens(t_proc *p, char *token, int id)
{
	while (p && p->next)
		p = p->next;
	token = check_token_expan(token, id);
	if (id == 0)
		save_tokens(&(p->as), token, id);
	else
		save_tokens(&(p->red), token, id);
	ft_memdel((void **)&token);
}

static int	check_execute(t_proc *p, t_tok *t, int check)
{
	if (t && t->id == 5)
		return (check_fork(p, 1));
	if (check == 1 && exit_status(0, 0))
	{
		free_process(p);
		if (t && t->id == 7)
			return (!ft_strcmp("&&", t->token) ? 1 : 2);
		return (0);
	}
	if (check == 2 && !exit_status(0, 0))
	{
		free_process(p);
		if (t && t->id == 7)
			return (!ft_strcmp("&&", t->token) ? 1 : 2);
		return (0);
	}
	if (t && t->id == 7)
		check = !ft_strcmp("&&", t->token) ? 1 : 2;
	else
		check = 0;
	check_fork(p, 0);
	return (check);
}

static void	separat_cmdl(t_tok *t)
{
	int		check;
	t_proc	*p;

	check = 0;
	while (t)
	{
		p = 0;
		if (g_exit)
			return ;
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
