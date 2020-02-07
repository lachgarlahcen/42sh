/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:08:29 by hastid            #+#    #+#             */
/*   Updated: 2020/02/07 02:29:02 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

static t_proc	*add_proc(void)
{
	t_proc	*pi;

	if (!(pi = (t_proc *)malloc(sizeof(t_proc))))
		return (0);
	pi->as = 0;
	pi->red = 0;
	pi->stat = 0;
	pi->next = 0;
	return (pi);
}

int				add_process(t_proc **procs)
{
	t_proc	*temp;

	if (*procs)
	{
		temp = *procs;
		while (temp->next)
			temp = temp->next;
		if (!(temp->next = add_proc()))
			return (1);
	}
	else if (!(*procs = add_proc()))
		return (1);
	return (0);
}

void			free_process(t_proc *p)
{
	t_proc	*tp;

	while (p)
	{
		tp = p->next;
		free_toks(p->as);
		free_toks(p->red);
		ft_memdel((void**)&p);
		p = tp;
	}
}
