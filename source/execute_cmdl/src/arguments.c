/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 04:58:13 by hastid            #+#    #+#             */
/*   Updated: 2020/02/18 05:51:15 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

int			is_intern_variable(char *name)
{
	int	i;

	i = 1;
	if (!ft_strchr(name, '='))
		return (1);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (1);
	while (name[i])
	{
		if (name[i] == '=')
			break ;
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int			check_all_arguments(t_proc *p)
{
	t_tok	*as;
	t_proc	*tp;

	tp = p;
	while (tp)
	{
		as = tp->as;
		while (as)
		{
			if (!is_intern_variable(as->token))
				as->id = 1;
			if (!as->id)
				break;
			as = as->next;
		}
		tp = tp->next;
	}
	return (0);
}

char		**get_args(t_tok *as)
{
	int		l;
	t_tok	*tmp;
	char	**args;

	l = 0;
	tmp = as;
	change_expansion(as);
	while (tmp)
	{
		if (!tmp->id && tmp->token)
			l++;
		tmp =  tmp->next;
	}
	if (!(args = (char **)malloc(sizeof(char *) * (l + 1))))
		return (0);
	l = 0;
	tmp = as;
	while (tmp)
	{
		if (tmp->token)
			args[l++] = ft_strdup(tmp->token);
		tmp = tmp->next;
	}
	args[l] = 0;
	return (args);
}
