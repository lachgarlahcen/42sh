/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_etoil.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 00:43:40 by hastid            #+#    #+#             */
/*   Updated: 2019/12/07 22:05:00 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	match(char *s1, char *s2)
{
	if (*s1 == '\0' && *s2 == '*')
		return (match(s1, s2 + 1));
	if (*s1 != '\0' && *s2 == '*')
		return ((match(s1 + 1, s2)) || (match(s1, s2 + 1)));
	if (*s1 == *s2 && *s2 != '\0')
		return (match(s1 + 1, s2 + 1));
	if (*s1 == '\0' && *s2 == '\0')
		return (1);
	return (0);
}

static char	*search_path(char *str)
{
	int		i;
	int		end;
	char	*path;

	i = 0;
	end = 0;
	while (str[i])
	{
		if (str[i] == '/')
			end = i;
		i++;
	}
	path = end ? ft_strsub(str, 0, end + 1) : ft_strdup(".");
	return (path);
}

static int	add_token(char *str, t_tok **toks, char *path)
{
	DIR				*dirp;
	char			*tmp;
	struct dirent	*dp;
	int				check;

	check = 0;
	dirp = opendir(path);
	if (!dirp)
		return (-1);
	while ((dp = readdir(dirp)))
	{
		tmp = ft_strcmp(".", path) ? ft_strjoin(path, dp->d_name)
			: ft_strdup(dp->d_name);
		if ((str[0] == '.' || dp->d_name[0] != '.') && match(tmp, str))
		{
			check = 1;
			if (save_tokens(toks, tmp, 0))
				return (-1);
		}
		ft_memdel((void **)&tmp);
	}
	closedir(dirp);
	return (check);
}

static int	save_etoil(t_tok **toks, char *str)
{
	int		ret;
	char	*path;

	if (!(path = search_path(str)))
		return (1);
	ret = add_token(str, toks, path);
	if (ret == -1)
		return (1);
	if (!ret)
		if (save_tokens(toks, str, 0))
			return (1);
	ft_memdel((void **)&path);
	return (0);
}

int			edit_etoile(t_tok **toks, char *str, int id)
{
	if (ft_strchr(str, '*'))
	{
		if (save_etoil(toks, str))
			return (1);
	}
	else if (save_tokens(toks, str, id))
		return (1);
	return (0);
}
