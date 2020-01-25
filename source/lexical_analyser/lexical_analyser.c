/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_analyser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:38:40 by hastid            #+#    #+#             */
/*   Updated: 2020/01/24 23:53:31 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexical_analyser.h"

int		free_perror(char *s1, char *s2, int check, int ret)
{
	if (s1)
		ft_memdel((void **)&s1);
	if (s2)
		ft_memdel((void **)&s2);
	if (check)
		ft_putendl("42sh: syntax error !!");
	return (ret);
}

int		parser(char *s, int be, int pl, t_tok **t)
{
	int		chk;
	char	*tp;
	char	*tmp;

	if (!(tmp = ft_strsub(s, be, pl - be)))
		return (0);
	if (isdelim(tmp[0]))
	{
		chk = g_check(0, 0);
		if (!(*t) || (g_check(0, 0) && g_check(0, 0) != 4) || syntax_analyser(tmp))
			return (free_perror(tmp, 0, 0, -1));
		if (chk == 4 && g_check(0, 0) == 3)
			return (free_perror(tmp, 0, 0, -1));
	}
	else if (isnumber(tmp) && g_check(0, 0))
		g_check(4, 1);
	else if (!ft_isblank(tmp[0]) || (ft_isblank(tmp[0]) && g_check(0, 0) == 4))
		g_check(0, 1);
	if (!isdelim(tmp[0]) && !ft_isblank(tmp[0]) && (tp = check_alias(tmp)))
		return (save_alias_tokens(tp, t, tmp));
	else
		save_tokens(t, tmp);
	return (0);
}

int		lexical_parser(char **line, t_tok **t)
{
	int		i;
	int		be;
	char	*s;

	i = 0;
	s = *line;
	while (s && s[i])
	{
		be = i;
		if (ft_isblank(s[i]) || s[i] == '\n')
			while (s[i] && (ft_isblank(s[i]) || s[i] == '\n'))
				i++;
		else if (isdelim(s[i]))
			while (s[i] && isdelim(s[i]))
				i++;
		else
			while (s[i] && !isdelim(s[i]) && !ft_isblank(s[i]) && s[i] != '\n')
				if ((i = isinhib(s[i]) ? end_inhibitors(&s, i, s[i]) : ++i) == -1)
					return (-1);
		if (s && i > be)
			if ((be = parser(s, be, i, t)))
				return (be);
	}
	*line = s;
	if (g_check(0, 0) == 1)
		return (1);
	if (g_check(0, 0) == 3)
		return (-1);
	return (0);
}

int		lexical_analyser(void)
{
	int		ret;
	char	*line;
	char	*temp;
	t_tok	*toks;

	ret = 1;
	toks = 0;
	g_check(0, 1);
	line = ft_strdup(save_environ(0)->line);
	while (ret)
	{
		ret = lexical_parser(&line, &toks);
		if (ret)
		{
			free_toks(toks);
			toks = 0;
			add_history(line); //tmp
			if (ret == -1 || !(temp = line_editing("$> ")))
				break ;
			line = strjoin_free(line, temp, 1, 1);
		}
	}
	add_history(line);
	add_to_environ(line, toks);
	ft_memdel((void **)&line);
	if (ret == 0)
		return (0);
	return (free_perror(0, 0, 1, 255));
}

int		g_check(int check, int init)
{
	static int	temp;

	if (init)
		temp = check;
	return (temp);
}
