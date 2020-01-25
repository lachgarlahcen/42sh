/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 01:50:50 by hastid            #+#    #+#             */
/*   Updated: 2020/01/25 00:53:35 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexical_analyser.h"

#include <readline/readline.h>
#include <readline/history.h>

int		is_value(char c, char q)
{
	if (c == ' ' || c == '&' || c == '|' || c == '>' || c == '<')
		return (0);
	if (c == 34 && q != 34)
		return (0);
	if (c == 39 && q != 39)
		return (0);
	return (1);
}

int		puterr_free(char *str, int free)
{
	ft_putstr("42sh: ");
	ft_putstr(str);
	ft_putendl(": event not found");
	if (free)
		ft_memdel((void **)&str);
	return (1);
}

char	*search_history(char *str)
{
	if (!ft_strcmp("ls", str))
		return (ft_strdup("ls >>"));
	if (!ft_strcmp("la", str))
		return (ft_strdup("ls &&"));
	if (!ft_strcmp("ld", str))
		return (ft_strdup("ls "));
	return (0);
}

char	*strjoin_free(char *s1, char *s2, int f1, int f2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (f1)
		ft_memdel((void **)&s1);
	if (f2)
		ft_memdel((void **)&s2);
	return (str);
}

int		new_line(char **str, int be, char *new)
{
	int		i;
	char	*tp;
	char	*nl;
	char	*tmp;

	tmp = *str;
	if (be)
	{
		tp = ft_strsub(tmp, 0, be);
		nl = strjoin_free(tp, new, 1, 0);
	}
	else
		nl = ft_strdup(new);
	i = be;
	while (tmp[i] && is_value(tmp[i], tmp[be]))
		i++;
	if (tmp[i])
	{
		tp = ft_strsub(tmp, i, ft_strlen(tmp) - i);
		nl = strjoin_free(nl, tp, 1, 1);
	}
	ft_memdel((void **)&tmp);
	*str = nl;
	return (0);
}

int		check_history(int be, char **line, int l)
{
	char	*tmp;
	char	*subs;

	subs = ft_strsub(*line, be, l);
	if ((tmp = search_history(subs)))
		new_line(line, be - 1, tmp);
	else
		return (puterr_free(subs, 1));
	ft_memdel((void **)&subs);
	ft_memdel((void **)&tmp);
	return (0);
}

int		expans_history(char **line)
{
	int		i;
	int		be;
	char	*tp;

	i = 0;
	tp = *line;
	while (tp[i])
	{
		if (tp[i] == '!')
		{
			i++;
			be = i;
			while (tp[i] && is_value(tp[i], tp[be]))
				i++;
			if (i > be)
			{
				if (check_history(be, &tp, i - be))
					return (1);
				i = be - 1;
			}
			else
				return (puterr_free("!", 0));
		}
		i++;
	}
	*line = tp;
	return (0);
}

char	*line_editing(char *str)
{
	char	*line;

	while (1)
	{
		if (!(line = readline(str)))
			return (0);
		if (!expans_history(&line))
			return (line);
		ft_memdel((void **)&line);
	}
	return (0);
}
