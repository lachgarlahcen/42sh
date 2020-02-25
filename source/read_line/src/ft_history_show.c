/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_show.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 05:33:04 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/24 23:55:56 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

static void		complet(char *choice, t_cmd *l)
{
	int i;

	i = 0;
	l->len = 0;
	l->cur = 0;
	while (choice && choice[i])
	{
		l->key = choice[i];
		add_at(l);
		i++;
	}
}

static int		readkey(char *buff, int *cur)
{
	int key;

	key = 0;
	read(0, &key, sizeof(int));
	if (key && ft_isprint(key))
	{
		buff[*cur] = key;
		buff[++*cur] = 0;
		key = 0;
	}
	return (key);
}

static int		match_key(char *buff, int *cur)
{
	int key;

	key = readkey(buff, cur);
	if (key == BACK_K)
		buff[*cur == 0 ? 0 : --*cur] = 0;
	if (key == ESC_K)
		return (0);
	if (key == INTER_K)
		return (2);
	return (1);
}

void			print_search_prompt(t_cmd *l, char *buff, char *res)
{
	char *promt;

	ft_putstr_fd(tgoto(CM, 0, l->init_p->r - 1), 0);
	ft_putstr_fd(CD, 1);
	promt = ft_strjoin_f(ft_strjoin("(reverse-i-search)`", buff),
			ft_strjoin("':", res ? res : ""), 1, 1);
	ft_putstr_fd(promt, 1);
	ft_strdel(&promt);
}

void			show_history(t_cmd *l)
{
	char	buff[BUFF_SIZE];
	char	*res;
	int		sig;
	int		cur;

	buff[0] = '\0';
	cur = 0;
	while (1337)
	{
		res = get_history_by_match(buff);
		print_search_prompt(l, buff, res);
		sig = match_key(buff, &cur);
		if (sig == 2)
		{
			complet(res, l);
			sig = 0;
		}
		if (res)
			free(res);
		if (!sig || l->ctl_c)
			break ;
	}
}
