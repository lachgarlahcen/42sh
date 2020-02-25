/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control_nodes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 06:59:13 by nsaber            #+#    #+#             */
/*   Updated: 2020/02/25 07:03:20 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

t_job		*jobs_plus_ret(t_job *j)
{
	while (j)
		{
			if (j->sign == '+')
				break ;
			if (!j->next)
				break ;
			j = j->next;
		}
		return (j);
}

t_job		*job_sign_finder(char sign)
{
	t_job *tmp;

	tmp = g_jobs.f_job;
	while (tmp)
	{
		if (sign == tmp->sign)
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

void		job_node_manpl_signs(t_job *tmp, t_job *j)
{
	tmp = g_jobs.f_job;
	while (tmp)
	{
		if (tmp->sign == '-' && j->sign == '-')
		{
			if (!(tmp = job_sign_finder(' ')))
				return ;
			tmp->sign = '-';
			break ;
		}
		if (tmp->sign == '+' && j->sign == '+')
		{
			if (!(tmp = job_sign_finder('-')))
				return ;
			tmp->sign = '+';
			if (!(tmp = job_sign_finder(' ')))
				return ;
			tmp->sign = '-';
			break ;
		}
		tmp = tmp->next;
	}
}

void		job_node_trait(t_job *j, int mines)
{
	t_job *tmp;
	int len;

	len = 0;
	if (!(j->sign) || j->sign == ' ')
		return ;
	tmp = g_jobs.f_job;
	while (tmp)
	{
		len = tmp->id;
		tmp = tmp->next;
	}
	if ((len == j->id && mines) || (len == 0 && mines))
		g_jobs.id--;
	job_node_manpl_signs(tmp, j);
}

int			check_ctr_jobs_args(char **args, t_job **j,char *str, int percent)
{
	if (args[1] && ft_isdigits(args[1]))
	{
		percent = args[1][0] == '%' ? 1 : 0;
		while (*j)
		{
			if ((*j)->id == ft_atoi(args[1] + percent))
				break ;
			*j = (*j)->next;
			if (!(*j))
			{
				ft_putstr_fd(str, 2);
				ft_putendl_fd(": %s no such job", 2);
				return (1);
			}
		}
	}
	else if (args[1])
	{
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": %s no such job", 2);
		return (1);
	}
	else
		*j = jobs_plus_ret(*j);
	return (0);
}
