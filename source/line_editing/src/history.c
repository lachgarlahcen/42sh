/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 04:55:08 by hastid            #+#    #+#             */
/*   Updated: 2020/02/13 23:54:06 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

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

int		check_history(char **str, int be, int q)
{
	int		i;
	char	*tp;
	char	*tmp;

	i = be;
	tp = *str;
	while (tp[i] && is_value(tp[i], tp[q]))
		i++;
	if (!(tp = ft_strsub(*str, be, i - be)))
		return (0);
	if (!(i > be) || !(tmp = search_history(tp)))
		return (ft_perror(tp, '!', ": event not found.", 1));
	ft_memdel((void **)&tp);
	if ((tp = ft_strsub(*str, 0, be - 1)))
		tmp = strjoin_free(tp, tmp, 1, 1);
	if ((tp = ft_strsub(*str, i, ft_strlen(*str) - i)))
		tmp = strjoin_free(tmp, tp, 1, 1);
	tp = *str;
	ft_memdel((void **)&(tp));
	*str = tmp;
	return (0);
}

int		check_history_expa(char **line)
{
	int		i;
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
			if (check_history(&str, ++i, qo))
				return (1);
		}
		else
			i++;
	}
	*line = str;
	return (0);
}
