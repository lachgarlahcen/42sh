/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 05:39:04 by llachgar          #+#    #+#             */
/*   Updated: 2019/12/01 01:21:27 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	free_out(t_cmd *l)
{
	if (l)
	{
		ft_bzero(l->chars, BUFF_SIZE);
		if (l->cur_p)
			free(l->cur_p);
		if (l->init_p)
			free(l->init_p);
		free(l);
		keep_l(NULL, 0);
	}
	ft_putchar('\n');
}

void	go_to_the_end(t_cmd *l)
{
	l->cur = l->len;
	print_cmd(l);
}
