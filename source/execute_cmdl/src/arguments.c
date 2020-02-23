/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 04:58:13 by hastid            #+#    #+#             */
/*   Updated: 2020/02/23 18:42:30 by aihya            ###   ########.fr       */
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

void		manage_hashtable(char *bin_name)
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
		if (as)
			manage_hashtable(as->token);
		tp = tp->next;
	}
	return (0);
}

char		*delet_quotes(char *str)
{
	int		i;
	int		j;
	int		be;
	char	buf[READ_SIZE];

	i = 0;
	j = 0;
	ft_bzero(buf, READ_SIZE);
	while (str[i] && i < READ_SIZE)
	{
		if (str[i] == '\\')
			i++;
		if (str[i] == '\'' || str[i] == '\"')
		{
			be = i++;
			while (str[i] && str[i] != str[be])
			{
				if (str[i] == '\\' && str[be] == '\"')
					i++;
				buf[j++] = str[i++];
			}
			i++;
		}
		buf[j++] = str[i];
		if (str[i])
			i++;
	}
	return (ft_strdup(buf));
}

char		**get_args(t_tok *as)
{
	int		l;
	t_tok	*tmp;
	char	**args;

	l = 0;
	if (!(tmp = as))
		return (0);
	while (tmp)
	{
		if (!tmp->id && tmp->token)
			l++;
		tmp = tmp->next;
	}
	if (!l || !(args = (char **)malloc(sizeof(char *) * (l + 1))))
		return (0);
	l = 0;
	tmp = as;
	while (tmp)
	{
		if (!tmp->id && tmp->token)
			args[l++] = delet_quotes(tmp->token);
		tmp = tmp->next;
	}
	args[l] = 0;
	return (args);
}

void		free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		ft_memdel((void **)&tab[i++]);
	free(tab);
	tab = 0;
}
