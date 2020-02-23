/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fc_redo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 22:24:39 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/23 00:53:50 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

static char		*ft_fc_get_cmd(t_fc *fc)
{
	t_hist	*hist;
	int		index;

	hist = NULL;
	hist = save_hist(&hist);
	if (!fc->first || fc->first[0] == '0')
		return (get_element_by_index(0, hist->hist_list));
	index = ft_atoi(fc->first);
	if (index < 0)
		return (get_element_by_index(index * -1 - 1, hist->hist_list));
	if (index > 0)
		return (get_element_by_index(hist->count - index, hist->hist_list));
	return (get_history_by_match(fc->first));
}

int				ft_fc_redo(t_fc *fc)
{
	char *cmd;

	cmd = NULL;
	if (!(cmd = ft_fc_get_cmd(fc)))
	{
		ft_putstr_fd("42sh: fc: no command found\n", 2);
		return (0);
	}
	ft_putendl(cmd);
	g_h = 1;
	add_to_hist(ft_strdup(cmd), 0);
	line_editing(cmd, 0);
	g_h = 0;
	return (1);
}
