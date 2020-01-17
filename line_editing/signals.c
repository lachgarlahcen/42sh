/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 00:29:11 by llachgar          #+#    #+#             */
/*   Updated: 2019/12/02 01:36:03 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	ctl_d(t_cmd *l)
{
	if (l->len == 0)
	{
		l->ctl_d = 1;
		l->res = 0;
	}
}

void	win_ch(int seg)
{
	t_cmd	*l;

	(void)seg;
	l = NULL;
	l = keep_l(l, 1);
	if (l != NULL)
	{
		ft_putstr_fd(CL, 1);
		get_cur_pos(l->init_p);
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &(l->w));
		print_cmd(l);
	}
}
