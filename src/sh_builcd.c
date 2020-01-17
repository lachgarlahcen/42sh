/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builcd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 02:26:55 by hastid            #+#    #+#             */
/*   Updated: 2019/12/14 02:47:22 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

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

	i = 0;
	p = 0;
	while (str[i] && p < READ_SIZE - 1)
	{
		buf[p++] = str[i];
		if (str[i] == '/')
			if (str[i + 1] == '.' && (str[i + 2] == '/' || !str[i + 2]))
				i++;
		i++;
	}
	buf[i] = '\0';
	ft_memdel((void **)&str);
	return (ft_strdup(buf));
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
