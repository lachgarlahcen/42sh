/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builcd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <nsaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 02:26:55 by hastid            #+#    #+#             */
/*   Updated: 2020/02/23 00:20:59 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd_builtin.h"

static char	*del_slash(char *str)
{
	int		i;
	int		p;
	char	buff[READ_SIZE];

	i = 0;
	p = 0;
	while (str[i] && p < READ_SIZE - 1)
	{
		buff[p++] = str[i];
		if (str[i] == '/')
			while (str[i + 1] && str[i + 1] == '/')
				i++;
		i++;
	}
	if (p > 1 && buff[p - 1] == '/')
		buff[p - 1] = '\0';
	buff[p] = '\0';
	ft_memdel((void **)&str);
	return (ft_strdup(buff));
}

static char	*del_point(char *str)
{
	int		i;
	int		p;
	char	buf[READ_SIZE];
	char	*tmp;

	i = 0;
	p = 0;
	ft_bzero(buf, READ_SIZE);
	while (str[i] && p < READ_SIZE - 1)
	{
		(str[0] == '.' && str[i + 2] == '/') ? i += 1 : 0;
		(str[i] == '/' && str[i + 1] == '.' && !str[i + 2]) ? i += 2 : 0;
		if (str[i] == '/' && str[i + 1] == '.' && str[i + 2] == '/')
			i += 2;
		if (str[i] == '.' && str[i + 1] == 0)
			i += 1;
		buf[p++] = str[i++];
	}
	buf[i] = '\0';
	if (ft_strstr(buf, "/./"))
		tmp = del_point(ft_strdup(buf));
	else
		tmp = buf;
	ft_memdel((void **)&str);
	return (ft_strdup(tmp));
}

static char	**tab_path(char *str)
{
	int		i;
	int		cont;
	char	**tab;

	i = 0;
	cont = 0;
	tab = ft_strsplit(str, '/');
	while (tab[i])
		i++;
	while (--i >= 0)
	{
		if (!ft_strcmp(tab[i], ".."))
		{
			tab[i][0] = '*';
			cont++;
		}
		else if (ft_strcmp(tab[i], "..") && cont)
		{
			tab[i][0] = '*';
			cont--;
		}
	}
	return (tab);
}

static char	*del_point2(char *str)
{
	int		i;
	char	*ret;
	char	*tmp;
	char	**tab;

	i = 0;
	ret = 0;
	tab = tab_path(str);
	while (tab[i])
	{
		if (tab[i][0] != '*')
		{
			tmp = ret ? ft_strjoin(ret, "/") : ft_strdup("/");
			ft_memdel((void **)&ret);
			ret = ft_strjoin(tmp, tab[i]);
			ft_memdel((void **)&tmp);
		}
		i++;
	}
	if (!ret)
		ret = ft_strdup("/");
	free_tab(tab);
	 //we need free tab here and else where
	ft_memdel((void **)&str);
	return (ret);
}

char		*path_of_link(char *dir, char *pwd)
{
	int		i;
	char	*tp;
	char	*tmp;

	i = 0;
	if (dir[0] == '/')
		tmp = ft_strdup(dir);
	else
	{
		if (!(tp = ft_strjoin(pwd, "/")))
			return (0);
		if (!(tmp = ft_strjoin(tp, dir)))
			return (0);
		ft_memdel((void **)&tp);
	}
	tmp = del_point(tmp);
	tmp = del_slash(tmp);
	tmp = del_point2(tmp);
	return (tmp);
}
