/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 00:10:03 by hastid            #+#    #+#             */
/*   Updated: 2020/02/03 23:48:06 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

char	*search_history(char *str)
{
	if (!ft_strcmp(str, "ls"))
		return (ft_strdup("ls -la"));
	return (0);
}

int		check_history(char **str, int p, int be)
{
	char	*tp;
	char	*tmp;

	if (!(tp = ft_strsub(*str, be, p - be)))
		return (0);
	if (!(p > be) || !(tmp = search_history(tp)))
		return (ft_perror(tp, '!', ": event not found.", 1));
	ft_memdel((void **)&tp);
	if ((tp = ft_strsub(*str, 0, be - 1)))
		tmp = strjoin_free(tp, tmp, 1, 1);
	if ((tp = ft_strsub(*str, p, ft_strlen(*str) - p)))
		tmp = strjoin_free(tmp, tp, 1, 1);
	ft_memdel((void **)&(*str));
	*str = tmp;
	return (0);
}

int		is_value(char c, char qo)
{
	if (c == ' ' || c == '&' || c == '|' || c == '>' || c == '<' || c == ';')
		return (0);
	if (c == 34 && qo == 34)
		return (0);
	if (c == 39 && qo == 39)
		return (0);
	return (1);
}

int		check_history_expa(char **line)
{
	int		i;
	int		be;
	int		qo;
	char	*str;

	i = 0;
	str = *line;
	while (str[i])
	{
		qo = 0;
		if (str[i] == '\'' || str[i] == '\"')
		{
			qo = i;
			while (str[i] && str[i] != '!')
				i++;
		}
		if (str[i] == '!' && str[i + 1] && str[i + 1] != ' ')
		{
			be = ++i;
			while (str[i] && is_value(str[i], str[qo]))
				i++;
			if (check_history(&str, i, be))
				return (1);
			i = be;
		}
		else
			i++;
	}
	if (ft_strcmp(str, *line))
		ft_putendl(str);
	*line = str;
	return (0);
}
