/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_keys.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:43:00 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/05 03:42:49 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

char	*get_element_by_index(int index, t_data *list)
{
	t_data	*tmp;
	int		i;

	tmp = list;
	i = 0;
	while (tmp)
	{
		if (i == index)
			return (tmp->data);
		tmp = tmp->next;
		i++;
	}
	return (NULL);
}

void	top_k(t_cmd *l)
{
	t_hist	*h;
	int		i;
	char	*data;

	h = NULL;
	h = save_hist(&h);
	if (l->h_p >= h->count - 1)
		return ;
	l->h_p++;
	if (l->h_p == 0)
	{
		if (h->tmp)
			free(h->tmp);
		h->tmp = ft_strdup(l->chars);
	}
	data = get_element_by_index(l->h_p, h->hist_list);
	ft_strcpy(l->chars, data);
	i = l->cur;
	l->len = ft_strlen(data);
	l->cur = l->len;
}

void	bottom_k(t_cmd *l)
{
	t_hist	*h;
	int		i;
	char	*data;

	h = NULL;
	h = save_hist(&h);
	if (l->h_p <= -1)
		return ;
	l->h_p--;
	i = l->cur;
	if (l->h_p == -1)
	{
		ft_strcpy(l->chars, h->tmp);
		l->len = ft_strlen(h->tmp);
		free(h->tmp);
		h->tmp = NULL;
	}
	else
	{
		data = get_element_by_index(l->h_p, h->hist_list);
		ft_strcpy(l->chars, data);
		l->len = ft_strlen(data);
	}
	l->cur = l->len;
}
