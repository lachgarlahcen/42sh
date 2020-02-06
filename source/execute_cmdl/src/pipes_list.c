/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 03:08:29 by hastid            #+#    #+#             */
/*   Updated: 2020/02/06 03:16:05 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

static t_pipe	*add_pipe(void)
{
	t_pipe	*pi;

	if (!(pi = (t_pipe *)malloc(sizeof(t_pipe))))
		return (0);
	pi->as = 0;
	pi->red = 0;
	pi->next = 0;
	return (pi);
}

int				add_pipes(t_pipe **pipes)
{
	t_pipe	*temp;

	if (*pipes)
	{
		temp = *pipes;
		while (temp->next)
			temp = temp->next;
		if (!(temp->next = add_pipe()))
			return (1);
	}
	else if (!(*pipes = add_pipe()))
		return (1);
	return (0);
}

void			free_pipes(t_pipe *p)
{
	t_pipe	*tp;

	while (p)
	{
		tp = p->next;
		free_toks(p->as);
		free_toks(p->red);
		ft_memdel((void**)&p);
		p = tp;
	}
}
