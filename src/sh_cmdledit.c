/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cmdledit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 23:07:53 by hastid            #+#    #+#             */
/*   Updated: 2019/12/20 10:13:08 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	check_valarg(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static char	*edit_tilda(char *str, t_env *env)
{
	int		i;
	char	*tmp;

	i = 1;
	if (!str[i] || str[i] == '/' || check_space(str[i]))
	{
		if (!(tmp = ft_getenv(env, "HOME")))
		{
			ft_perror(0, "HOME: not exists", 1);
			return (0);
		}
		return (ft_strjoin(tmp, str + 1));
	}
	if (!(tmp = ft_strjoin("/Users/", str + 1)))
		return (0);
	if (!access(tmp, F_OK))
		return (tmp);
	ft_memdel((void **)&tmp);
	return (ft_strdup(str));
}

static char	*edit_dollar(char *str, t_env *env)
{
	int		i;
	char	*tp;
	char	*tmp;
	char	*name;

	i = 0;
	str++;
	name = 0;
	while (str[i] && check_valarg(str[i]))
		i++;
	if (!(tp = ft_strsub(str, 0, i)))
		return (0);
	if (!(name = ft_getenv(env, tp)))
		name = "\0";
	tmp = ft_strsub(str + i, 0, ft_strlen(str + i));
	if (tmp)
		name = ft_strjoin(name, tmp);
	else
		name = ft_strdup(name);
	ft_memdel((void **)&tp);
	ft_memdel((void **)&tmp);
	return (name);
}

static char	*join_line(char *tmp, int i, t_env *env, int check)
{
	char	*tp1;
	char	*tp2;

	if (!tmp)
		return (0);
	if ((tp1 = ft_strsub(tmp, 0, i)))
	{
		if (!check)
			tp2 = edit_tilda(tmp + i, env);
		else
			tp2 = edit_dollar(tmp + i, env);
		ft_memdel((void **)&tmp);
		if (!tp2)
		{
			ft_memdel((void **)&tp1);
			return (0);
		}
		if (!(tmp = ft_strjoin(tp1, tp2)))
			return (0);
		ft_memdel((void **)&tp1);
		ft_memdel((void **)&tp2);
	}
	return (tmp);
}

char		*parse_line(char *tmp, t_env *env)
{
	int		i;
	int		be;

	i = 0;
	while (tmp && tmp[i])
	{
		if (tmp[i] == '~' && (i == 0 || check_space(tmp[i - 1])))
			if (!(tmp = join_line(tmp, i, env, 0)))
				return (0);
		if (tmp[i] == '$' && check_valarg(tmp[i + 1]))
			if (!(tmp = join_line(tmp, i, env, 1)))
				return (0);
		if (tmp[i] == 34 || tmp[i] == 39)
		{
			be = i;
			while (tmp[++i] && tmp[i] != tmp[be])
				if (tmp[be] == 34 && tmp[i] == '$' && check_valarg(tmp[i + 1]))
					if (!(tmp = join_line(tmp, i, env, 1)))
						return (0);
			i++;
		}
		else
			i++;
	}
	return (tmp);
}
