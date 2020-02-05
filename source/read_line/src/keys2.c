/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 17:30:16 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/05 03:42:49 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_line.h"

void	end_k(t_cmd *l)
{
	l->cur = l->len;
}

void	home_k(t_cmd *l)
{
	l->cur = l->b_p;
}

void	return_k(t_cmd *l)
{
	l->res = 0;
}

void	ctl_left(t_cmd *l)
{
	int c;
	int s;

	c = 0;
	s = 0;
	while (--l->cur >= l->b_p)
	{
		if (ft_isalnum(l->chars[l->cur]))
		{
			c = 1;
			s = 0;
		}
		else
			s = 1;
		if (c && s)
		{
			l->cur++;
			return ;
		}
	}
	l->cur++;
}

void	ctl_right(t_cmd *l)
{
	int c;
	int s;

	c = 0;
	s = 0;
	while (l->cur < l->len)
	{
		if (!ft_isalnum(l->chars[l->cur]))
		{
			c = 0;
			s = 1;
		}
		else
			c = 1;
		if (c && s)
			return ;
		l->cur++;
	}
}
