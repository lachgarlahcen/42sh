/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 04:36:42 by hastid            #+#    #+#             */
/*   Updated: 2020/02/25 04:41:08 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

static int	is_intern_variable(char *name)
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

static void	delet_quotes_red(t_proc *p)
{
	t_tok	*as;
	t_proc	*tp;
	char	*tmp;

	tp = p;
	while (tp)
	{
		as = tp->red;
		while (as)
		{
			tmp = as->token;
			as->token = delet_quotes(tmp);
			ft_memdel((void **)&tmp);
			as = as->next;
		}
		tp = tp->next;
	}
}

static void	manage_hashtable(char *bin_name)
{
	char	*bin_path;

	if (is_binary(bin_name))
		hit_binary(bin_name);
	else if (!is_builtin(bin_name) && (bin_path = get_bin_path(bin_name)))
	{
		save_binary(bin_name, bin_path);
		hit_binary(bin_name);
		ft_strdel(&bin_path);
	}
}

static void	delet_quotes_arg(t_proc *p)
{
	t_tok	*as;
	t_proc	*tp;
	char	*tmp;

	tp = p;
	while (tp)
	{
		as = tp->as;
		while (as)
		{
			tmp = as->token;
			as->token = delet_quotes(tmp);
			ft_memdel((void **)&tmp);
			as = as->next;
		}
		as = tp->as;
		while (as && as->id)
			as = as->next;
		if (as)
			manage_hashtable(as->token);
		tp = tp->next;
	}
	delet_quotes_red(p);
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
				break ;
			as = as->next;
		}
		tp = tp->next;
	}
	delet_quotes_arg(p);
	return (0);
}
