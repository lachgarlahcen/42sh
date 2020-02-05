/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 15:17:56 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/05 03:42:49 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	alt_l_k(t_cmd *l)
{
	l->is_s = 1;
	if (l->cur - l->s_sp <= l->b_p)
		return ;
	l->s_sp++;
}

void	alt_d_k(t_cmd *l)
{
	int i;

	if (ft_strlen(l->cpy) == 0)
		return ;
	i = 0;
	while (l->cpy[i])
	{
		l->key = l->cpy[i];
		add_at(l);
		i++;
	}
}

void	alt_u_k(t_cmd *l)
{
	int i;
	int min;
	int max;

	if (!l->s_sp)
		return ;
	min = l->cur - l->s_sp;
	max = l->cur;
	i = 0;
	while (min <= max)
		l->cpy[i++] = l->chars[min++];
	l->cpy[i] = 0;
}

void	alt_x_k(t_cmd *l)
{
	if (!l->s_sp)
		return ;
	alt_u_k(l);
	l->cur != l->len ? l->cur++ : l->s_sp--;
	while (l->s_sp-- >= 0)
		delete(l);
}
