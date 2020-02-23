/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_selectmatch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 06:23:37 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/23 17:40:10 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

static int		readkey(void)
{
	long key;

	key = 0;
	read(0, &key, sizeof(long));
	return (key);
}

t_data			*listmatches(t_data *tmp, t_cmd *l, int sel)
{
	t_data	*choice;
	int		i;
	int		j;

	i = -1;
	j = 0;
	ft_putstr_fd(tgoto(CM, 0, 0), 1);
	ft_putstr_fd(CD, 1);
	while (tmp)
	{
		if (++i == sel)
			choice = tmp;
		if (i >= sel && l->w.ws_row - 1 >= j)
		{
			ft_putstr_fd(tgoto(CM, 0, j), 1);
			ft_putstr_fd(CE, 1);
			(sel == i) ? ft_putstr_fd("\033[1m\033[01;32m➜ ", 1) : 0;
			ft_putstr_fd(tmp->data, 1);
			(sel == i) ? ft_putstr_fd("\033[0m", 1) : 0;
			j++;
		}
		tmp = tmp->next;
	}
	return (choice);
}

int				matchkey(int key, int count, int *sel, t_cmd *l)
{
	if (key == BOTTOM_K)
		*sel = (*sel == count - 1) ? 0 : *sel + 1;
	if (key == TOP_K)
		*sel = (*sel == 0) ? count - 1 : *sel - 1;
	if (key == ESC_K || l->ctl_c)
	{
		ft_putstr_fd(TE, 0);
		ft_putstr_fd(VE, 0);
		return (0);
	}
	if (key == INTER_K)
		return (1);
	return (-1);
}

static void		complet(t_data *choice, t_cmd *l, char *match)
{
	int i;

	i = ft_strlen(match);
	ft_putstr_fd(TE, 0);
	ft_putstr_fd(VE, 0);
	while (choice->data[i])
	{
		l->key = choice->data[i];
		add_at(l);
		i++;
	}
}

void			print_matches(t_data *matches, t_cmd *l, int count, char *match)
{
	int		key;
	int		sel;
	int		res;
	int		cur;
	t_data	*choice;

	sel = 0;
	cur = l->cur;
	ft_putstr_fd(TI, 1);
	ft_putstr_fd(VI, 1);
	while (1337)
	{
		choice = listmatches(matches, l, sel);
		key = readkey();
		res = matchkey(key, count, &sel, l);
		if (res == 0)
			break ;
		if (res == 1)
		{
			complet(choice, l, match);
			break ;
		}
	}
}
