/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 02:01:17 by hastid            #+#    #+#             */
/*   Updated: 2020/01/24 23:54:17 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexical_analyser.h"

int		isinhib(char ch)
{
	if (ch == 34 || ch == 39 || ch == 92)
		return (1);
	return (0);
}

int		isdelim(char ch)
{
	if (ch == '|' || ch == '&' || ch == '<' || ch == '>' || ch == ';')
		return (1);
	return (0);
}

int		isnumber(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int		end_inhibitors(char **s, int p, char ch)
{
	int		i;
	char	*tp;
	char	*tmp;

	i = p + 1;
	while (1)
	{
		tp = *s;
		if (ch == 92 && tp[i])
			return (i + 1);
		if (ch == 34 || ch == 39)
			while (tp[i] && tp[i] != ch)
				i++;
		if (tp[i])
			return (i + 1);
		if (!(tmp = line_editing("$> ")))
			return (-1);
		if (ch == 34 || ch == 39)
			tp = strjoin_free(tp, "\n", 1, 0);
		*s = strjoin_free(tp, tmp, 1, 1);
	}
	return (0);
}
