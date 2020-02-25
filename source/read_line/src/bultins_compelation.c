/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bultins_compelation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 05:48:48 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/25 06:10:01 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

char		**get_bultins_tab(void)
{
	char **tab;

	if ((tab = (char **)malloc(sizeof(char *) * 15)))
		return (NULL);
	tab[0] = "fg";
	tab[0] = "bg";
	tab[0] = "test";
	tab[0] = "fc";
	tab[0] = "set";
	tab[0] = "echo";
	tab[0] = "type";
	tab[0] = "jobs";
	tab[0] = "hash";
	tab[0] = "exit";
	tab[0] = "unset";
	tab[0] = "alias";
	tab[0] = "export";
	tab[0] = "unalias";
	tab[0] = "cd";
	return (tab);
}

int			fill_bultins(char *match, t_data **matches)
{
	char		**tab;
	int			res;
	int			i;
	t_data		*new_match;

	tab = get_bultins_tab();
	res = 0;
	if (!tab)
		return (res);
	i = 0;
	while (tab[i])
	{
		if (!ft_memcmp(match, tab[i], ft_strlen(match)))
		{
			new_match = new_node(ft_strdup(tab[i]));
			sortedisert(matches, new_match);
			res++;
		}
		i++;
	}
	ft_chain_free(&tab);
	return (res);
}
