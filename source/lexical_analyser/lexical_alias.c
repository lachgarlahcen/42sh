/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 00:26:18 by hastid            #+#    #+#             */
/*   Updated: 2020/01/24 23:52:47 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexical_analyser.h"

char		*check_alias(char *al)
{
	if (!ft_strcmp("lob", al))
		return (ft_strdup("ls >> asa \n  >> ll"));
	return (0);
}

static int	parse_alias(char *s, int be, int pl, t_tok **toks)
{
	int		check;
	char	*tmp;

	if (!(tmp = ft_strsub(s, be, pl - be)))
		return (0);
	if (isdelim(tmp[0]))
	{
		check = g_check(0, 0);
		if (!(*toks) || (g_check(0, 0) && g_check(0, 0) != 4) || syntax_analyser(tmp))
			return (free_perror(tmp, s, 0, 1));
		if (check == 4 && g_check(0, 0) == 3)
			return (free_perror(tmp, s, 0, 1));
	}
	else if (isnumber(tmp) && g_check(0, 0))
		g_check(4, 1);
	else if (!ft_isblank(tmp[0]) || (ft_isblank(tmp[0]) && g_check(0, 0) == 4))
		g_check(0, 1);
	save_tokens(toks, tmp);
	return (0);
}

static int	end_inhib(char **s, int p, char ch)
{
	int		i;
	char	*tp;
	char	*tmp;

	i = p + 1;
	while (1)
	{
		tp = *s;
		if (ch == 34 || ch == 39)
			while (tp[i] && tp[i] != ch)
				i++;
		if (ch == 92)
			continue ;
		if (tp[i])
			return (i + 1);
		if (!(tmp = line_editing("$> ")))
			return (-1);
		if (ch == 34 || ch == 39)
			tp = strjoin_free(tp, "\n", 1, 0);
		*s = strjoin_free(tp, tmp, 1, 1);
	}
}

int			save_alias_tokens(char *al, t_tok **t, char *tmp)
{
	int		i;
	int		be;

	i = 0;
	ft_memdel((void **)&tmp);
	while (al[i])
	{
		be = i;
		if (ft_isblank(al[i]) || al[i] == '\n')
			while (al[i] && (ft_isblank(al[i]) || al[i] == '\n'))
				i++;
		else if (isdelim(al[i]))
			while (al[i] && isdelim(al[i]))
				i++;
		else
			while (al[i] && !isdelim(al[i]) && !ft_isblank(al[i]) && al[i] != '\n')
				if ((i = isinhib(al[i]) ? end_inhib(&al, i, al[i]) : ++i) == -1)
					return (-1);
		if (i > be)
			if (parse_alias(al, be, i, t))
				return (-1);
	}
	ft_memdel((void **)&al);
	return (0);
}
