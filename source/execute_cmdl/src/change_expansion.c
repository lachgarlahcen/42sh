/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 05:15:41 by hastid            #+#    #+#             */
/*   Updated: 2020/02/25 04:08:52 by hastid           ###   ########.fr       */
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
				if (str[i] == '\\')
					i++;
				else if (str[i] == '$' && str[i + 1] == '{' && str[be] == '\"')
					return (1);
				i++;
			}
		}
		if (str[i] == '\\')
			i++;
		else if (str[i] == '$' && str[i + 1] == '{')
			return (1);
		i = (str[i] != '\0') ? i + 1 : i;
	}
	return (0);
}

void	change_string(char **str, int be)
{
	int		i;
	char	*tp1;
	char	*tp2;
	char	*tmp;

	i = be;
	tp2 = 0;
	tmp = *str;
	while (tmp[i] && tmp[i] != '}')
		i++;
	if (!(tp1 = ft_strsub(tmp, be, i - be)))
		return ;
	if (!ft_strcmp("?", tp1) || !ft_strcmp("$", tp1))
		tp2 = ft_itoa(ft_strcmp("$", tp1) ? exit_status(0, 0) : getpid());
	else
		tp2 = get_variable(tp1);
	ft_memdel((void **)&tp1);
	if (!tp2)
		tp2 = ft_strdup("\0");
	tp1 = ft_strsub(tmp, 0, be - 2);
	tp2 = strjoin_free(tp1, tp2, 1, 1);
	tp1 = ft_strsub(tmp, i + 1, ft_strlen(tmp) - i - 1);
	tp2 = strjoin_free(tp2, tp1, 1, 1);
	ft_memdel((void **)&tmp);
	*str = tp2;
}

char	*change_dollar(char *tmp)
{
	int		i;
	int		be;

	i = 0;
	while (tmp[i])
	{
		if (tmp[i] == '\"' || tmp[i] == '\'')
		{
			be = i++;
			while (tmp[i] && tmp[i] != tmp[be])
			{
				if (tmp[i] == '\\' && tmp[be] == '\"')
					i++;
				else if (tmp[i] == '$' && tmp[i + 1] == '{' && tmp[be] == '\"')
					change_string(&tmp, i + 2);
				i++;
			}
		}
		if (tmp[i] == '\\')
			i++;
		else if (tmp[i] == '$' && tmp[i + 1] == '{')
			change_string(&tmp, i + 2);
		i = (tmp[i] != '\0') ? i + 1 : i;
	}
	return (tmp);
}

char	*change_tilda(char *str)
{
	char	*tp;
	char	*tmp;

	tmp = 0;
	if (str[1] == '\0' || str[1] == '/')
	{
		if (!(tp = get_variable("HOME")))
			return (str);
		tmp = strjoin_free(tp, str + 1, 1, 0);
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

char	*check_token_expan(char *str, char id)
{
	char	*tp;

	tp = 0;
	str = ft_strdup(str);
	if (str[0] == '~')
		return (change_tilda(str));
	if (check_dollar(str))
		tp = change_dollar(ft_strdup(str));
	else
		return (str);
	if (tp && !(*tp))
		ft_memdel((void **)&tp);
	if (!tp && id)
		return (str);
	ft_memdel((void **)&str);
	return (tp);
}
