/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:29:11 by llachgar          #+#    #+#             */
/*   Updated: 2019/11/30 00:36:39 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	right_key(t_cmd *l)
{
	if (l->cur >= l->len)
		return ;
	l->cur++;
}

void	left_key(t_cmd *l)
{
	if (l->cur - l->b_p <= 0)
		return ;
	l->cur--;
}

void	delete(t_cmd *l)
{
	int	i;

	if (l->cur - l->b_p <= 0)
		return ;
	i = l->cur - 1;
	while (i < l->len)
	{
		l->chars[i] = l->chars[i + 1];
		i++;
	}
	l->len--;
	l->cur--;
}

void	down_k(t_cmd *l)
{
	int i;
	int p;

	i = l->cur;
	p = 0;
	while (--i >= 0 && l->chars[i] != '\n')
		p++;
	i = l->cur;
	while (i < l->len && l->chars[i] != '\n')
		i++;
	if (i == l->len)
		return ;
	p += i++;
	p++;
	while (i < l->len && l->chars[i] != '\n')
		i++;
	if (i < p)
		l->cur = i;
	else
		l->cur = p;
}

void	up_k(t_cmd *l)
{
	int i;
	int p;

	i = l->cur;
	p = 0;
	while (--i >= 0 && l->chars[i] != '\n')
		p++;
	if (--i <= 0)
		return ;
	while (i >= 0 && l->chars[i] != '\n')
		i--;
	p += i++;
	p++;
	while (l->chars[i] != '\n')
		i++;
	if (i < p)
		l->cur = i;
	else
		l->cur = p;
}
