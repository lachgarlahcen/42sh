/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 05:15:41 by hastid            #+#    #+#             */
/*   Updated: 2020/02/20 11:13:00 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmdl.h"

int		check_dollar(char *str)
{
	int	i;
	int	be;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			be = i++;
			while (str[i] && str[i] != str[be])
			{
				if (str[i] == '$' && str[i + 1] == '{' && str[be] == '\"')
					return (1);
				i++;
			}
		}
		if (str[i] == '$' && str[i + 1] == '{')
			return (1);
		i++;
	}
	return (0);
}

char	*change_tilda(char *str)
{
	char	*tp;
	char	*tmp;

	tmp = 0;
	if (str[1] == '\0' || str[1] == '/')
	{
		if (!(tp = get_variable("HOME")))
			return (0); // err  HOME not set
		tmp = ft_strjoin(tp, str + 1);
		ft_memdel((void **)&tp);
		ft_memdel((void **)&str);
	}
	else
	{
		tmp = ft_strjoin("/Users/", str + 1);
		if (access(tmp, F_OK))
		{
			ft_memdel((void **)&tmp);
			tmp = str;
		}
		else
			ft_memdel((void **)&str);
	}
	return (tmp);
}

char	*change_string(char *str, int be)
{
	int		i;
	char	*tp;
	char	*tmp;

	i = be;
	tp = 0;
	while (str[i] && str[i] != '}')
		i++;	
	tp = ft_strsub(str, be, i - be);
	if (!ft_strcmp("?", tp))
		tmp = ft_itoa(exit_status(0, 0));
	else if (!ft_strcmp("$", tp))
		tmp = ft_itoa(getpid());
	else
		tmp = get_variable(tp);
	ft_memdel((void **)&tp);
	tp = ft_strsub(str, 0, be - 2);
	if (tmp)
		tp = strjoin_free(tp, tmp, 1, 1);
	tmp = ft_strsub(str, i + 1, ft_strlen(str) - i - 1);
	tp = strjoin_free(tp, tmp, 1, 1);
	if (!*tp)
		ft_memdel((void **)&tp);
	return (tp);
}

char	*change_dollar(char *str, int id)
{
	int		i;
	int		be;
	char	*tmp;

	i = 0;
	tmp = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			be = i++;
			while (str[i] && str[i] != str[be])
			{
				if (str[i] == '$' && str[i + 1] == '{' && str[be] == '\"')
					return (tmp = change_string(str, i + 2));
				i++;
			}
		}
		if (str[i] == '$'  && str[i + 1] == '{')
			tmp = change_string(str, i + 2);
		i++;
	}
	if (!tmp && id != 0)
		return (str);
	ft_memdel((void **)&str);
	return (tmp);
}
int		change_expansion(t_tok *t)
{
	while (t)
	{
		if (t->token && t->token[0] == '~')
			if (!(t->token = change_tilda(t->token)))
				return (1);
		if (check_dollar(t->token))
			t->token = change_dollar(t->token, t->id);
		t = t->next;
	}
	return (0);
}
