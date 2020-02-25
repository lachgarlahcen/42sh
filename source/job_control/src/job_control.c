/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 22:18:53 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/25 07:09:50 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

char	*name_list_concate(t_proc *p, char *name_args, char *tmp, t_tok *ptr)
{
	name_args = 0;
	if ((ptr = p->as))
		name_args = ft_strdup(ptr->token);
	while (ptr && ptr->next)
	{
		tmp = strjoin_free(name_args, " ", 1, 0);
		ptr = ptr->next;
		name_args = strjoin_free(tmp, ptr->token, 1, 0);
	}
	if ((ptr = p->red))
	{
		if (!name_args)
			name_args = ft_strdup(ptr->token);
		else
			name_args = strjoin_free(name_args, ptr->token, 1, 0);
		while (ptr && ptr->next)
		{
			tmp = strjoin_free(name_args, " ", 1, 0);
			ptr = ptr->next;
			name_args = strjoin_free(tmp, ptr->token, 1, 0);
		}
	}
	return (name_args);
}

void	job_printing(char option)
{
	t_job *j;

	j = g_jobs.f_job;
	while (j)
	{
		j->notified = 1;
		format_job_info(j, option);
		j = j->next;
		if (!(option == 'l' || option == 'p' || option == 0))
			break ;
	}
}

int		ft_isdigits(char *str)
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

int			job_arg_option(char *option, char **args)
{
	int i;

	i = 0;
	while (args[1][++i])
	{
		*option = args[1][i];
		if (!(args[1][i] == 'l' || args[1][i] == 'p'))
		{
			*option = args[1][i];
			ft_putendl_fd("jobs: -%c: invalid option : jobs [-lp]", 2);
			return (1);
		}
	}
	if (args[2])
	{
		execute_jobs(args + 1);
		*option = 0;
		return (0);
	}
	job_printing(*option);
	return (0);
}

int			job_arg(char **args, char *option, int i)
{
	t_job	*jj;
	t_job	*j;
	int		percent;

	j = g_jobs.f_job;
	jj = j;
	args[1][0] == '%' ? percent = 1 : 0;
	while (j)
	{
		if (args[i] && (ft_strequ(args[i], j->cmd) ||
		(ft_isdigits(args[i]) && ft_atoi(args[i] + percent) == j->id)))
		{
			i++;
			format_job_info(j, *option);
			j = jj;
		}
		else
			j = j->next;
		if (!j && args[i])
		{
			ft_putendl_fd("jobs: job not found: %s", 2);
			return (1);
		}
	}
	return (0);
}

int			execute_jobs(char **args)
{
	t_job		*j;
	int			i;
	static char	option = 0;

	update_status();
	i = 0;
	j = g_jobs.f_job;
	if (args[1] && args[1][0] == '-' && job_arg_option(&option, args))
		return (1);
	else if (args[1] && job_arg(args, &option, 1))
		return(1);
	else
		job_printing(option);
	option = 0;
	return(0);
}

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

int			execute_fg(char **args)
{
	t_job	*j;

	if (getpid() != g_shell_pgid)
	{
		ft_putendl_fd("fg: no job control", 2);
		return (1);
	}
	j = g_jobs.f_job;
	if (args [1] && args[1][0] == '-' && args[1][1])
	{
		ft_putendl_fd("fg: invalid option fg [job_spec]", 2);
		return(1);
	}
	if (!j)
	{
		ft_putendl_fd("fg: current: no such job", 2);
		return(1);
	}
	if (check_ctr_jobs_args(args, &j, "42sh : fg", 0))
		return(1);
	put_job_in_foreground(j, 1);
	return(0);
}

int			execute_bg(char **args)
{
		t_job	*j;

	if (getpid() != g_shell_pgid)
	{
		ft_putendl_fd("bg: no job control", 2);
		return (1);
	}
	j = g_jobs.f_job;
	if (args [1] && args[1][0] == '-' && args[1][1])
	{
		ft_putendl_fd("bg: invalid option bg [job_spec]", 2);
		return(1);
	}
	if (!j)
	{
		ft_putendl_fd("bg: current: no such job", 2);
		return(1);
	}
	if (check_ctr_jobs_args(args, &j, "42sh : bg", 0))
		return(1);
	put_job_in_background(j, 1);
	return(0);
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

void		job_node_manpl_signs(t_job *tmp)
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
	job_node_manpl_signs(tmp);
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
