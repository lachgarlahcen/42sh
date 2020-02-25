/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 04:58:13 by hastid            #+#    #+#             */
/*   Updated: 2020/02/25 04:40:42 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

char		*delet_quotes(char *str)
{
	int		j;
	char	be;
	char	buf[READ_SIZE];

	j = 0;
	ft_bzero(buf, READ_SIZE);
	while (*str && j < READ_SIZE)
	{
		if (*str == '\\')
			str++;
		else if (*str == '\'' || *str == '\"')
		{
			be = *str++;
			while (*str && *str != be)
			{
				if (*str == '\\' && be == '\"')
					str++;
				buf[j++] = *str++;
			}
			str++;
		}
		buf[j++] = *str;
		str = (*str != '\0') ? str + 1 : str;
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
			args[l++] = ft_strdup(tmp->token);
		tmp = tmp->next;
	}
	args[l] = 0;
	return (args);
}

void		free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			ft_memdel((void **)&tab[i++]);
		free(tab);
		tab = 0;
	}
}
