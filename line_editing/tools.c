/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 19:23:41 by llachgar          #+#    #+#             */
/*   Updated: 2019/12/01 22:57:14 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void		get_cur_pos(t_point *t)
{
	char	pos[20];
	int		i;

	ft_putstr_fd("\e[6n", 0);
	ft_bzero(pos, 20);
	i = read(0, pos, 20);
	pos[i] = 0;
	i = 2;
	t->r = ft_atoi(pos + i);
	while (ft_isdigit(pos[i]))
		i++;
	t->c = ft_atoi(pos + i + 1);
}

void		mines(t_point *p, t_cmd *l)
{
	if (p->c > 0)
	{
		p->c--;
	}
	else
	{
		p->c = l->w.ws_col - 1;
		p->r--;
	}
}

void		plus(t_point *p, t_cmd *l, t_point *p1, int i)
{
	if (p->c == l->w.ws_col - 1 || l->chars[i] == '\n')
	{
		p->c = 0;
		if (p->r == (l->w.ws_row - 1))
		{
			l->init_p->r--;
			p1->r--;
			ft_putstr_fd(DO, 1);
		}
		else
			p->r++;
		ft_putstr_fd(tgoto(CM, p->c, p->r), 1);
	}
	else
		p->c++;
}

void		sheft(t_cmd *l)
{
	int i;

	i = l->len;
	while (i >= l->cur)
	{
		l->chars[i] = l->chars[i - 1];
		i--;
	}
	l->chars[l->cur] = (int)l->key;
}

void		add_at(t_cmd *l)
{
	if (l->cur == l->len)
		l->chars[l->cur] = (int)l->key;
	else
	{
		sheft(l);
	}
	l->len++;
	l->cur++;
	l->chars[l->len] = '\0';
}
