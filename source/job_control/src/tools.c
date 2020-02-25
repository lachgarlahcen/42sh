/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 06:59:13 by nsaber            #+#    #+#             */
/*   Updated: 2020/02/25 07:01:06 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

void		job_sign(t_job *j)
{
	t_job *tmp;
	int len;

	tmp = g_jobs.f_job;
	len = 0;
	while (tmp)
    {
        if (tmp->sign == '-' && (j->sign != '+' ))
            tmp->sign = ' ';
        if (tmp->sign == '+')
            tmp->sign = '-';
        len++;
        tmp = tmp->next;
    }
	j->sign = '+';
}
