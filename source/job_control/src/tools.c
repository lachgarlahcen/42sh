/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 06:59:13 by nsaber            #+#    #+#             */
/*   Updated: 2020/02/25 19:14:22 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

void		job_sign(t_job *j)
{
	t_job	*tmp;
	int		len;

	tmp = g_jobs.f_job;
	len = 0;
	while (tmp)
	{
		if (tmp->sign == '-' && (j->sign != '+'))
			tmp->sign = ' ';
		if (tmp->sign == '+')
			tmp->sign = '-';
		len++;
		tmp = tmp->next;
	}
	j->sign = '+';
}

int			ft_isdigits(char *str)
{
	if (str)
	{
		if (*str == '%')
			str++;
		while (*str)
		{
			if (ft_isdigit(*str))
				str++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}

char		*name_list_concate(t_proc *p, char *nm_args, char *tmp, t_tok *ptr)
{
	nm_args = 0;
	if ((ptr = p->as))
		nm_args = ft_strdup(ptr->token);
	while (ptr && ptr->next)
	{
		tmp = strjoin_free(nm_args, " ", 1, 0);
		ptr = ptr->next;
		nm_args = strjoin_free(tmp, ptr->token, 1, 0);
	}
	if ((ptr = p->red))
	{
		if (!nm_args)
			nm_args = ft_strdup(ptr->token);
		else
			nm_args = strjoin_free(nm_args, ptr->token, 1, 0);
		while (ptr && ptr->next)
		{
			tmp = strjoin_free(nm_args, " ", 1, 0);
			ptr = ptr->next;
			nm_args = strjoin_free(tmp, ptr->token, 1, 0);
		}
	}
	return (nm_args);
}

void		put_job_in_foreground(t_job *j, int cont)
{
	tcsetpgrp(STDIN_FILENO, j->pgid);
	if (cont)
	{
		if (killpg(j->pgid, SIGCONT) < 0)
			perror("kill (SIGCONT)");
	}
	wait_for_job(j);
	tcsetpgrp(STDIN_FILENO, g_shell_pgid);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &g_shell_tmodes);
	if (job_is_completed(j))
	{
		job_node_trait(j, 1);
		delete_job(j->pgid);
	}
	else
	{
		if (j->id == 0)
			j->id = g_jobs.id++;
		job_sign(j);
	}
}

void		put_job_in_background(t_job *j, int cont)
{
	if (cont)
		killpg(j->pgid, SIGCONT);
	else
		ft_printf("[%d] %ld\n", j->id, j->pgid);
}
