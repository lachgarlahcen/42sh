/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 00:46:23 by hastid            #+#    #+#             */
/*   Updated: 2020/02/04 03:29:08 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_parser.h"

int		is_number(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int		token_analyzer(char *str, int check)
{
	if (check && is_number(str))
		return (1);
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<"))
		return (2);
	if (!ft_strcmp(str, ">>") || !ft_strcmp(str, "<<"))
		return (2);
	if (!ft_strcmp(str, "&>") || !ft_strcmp(str, "<&"))
		return (2);
	if (!ft_strcmp(str, ">&") || !ft_strcmp(str, "&<"))
		return (2);
	if (!ft_strcmp(str, "|"))
		return (4);
	if (!ft_strcmp(str, "&"))
		return (5);
	if (!ft_strcmp(str, ";"))
		return (6);
	if (!ft_strcmp(str, "&&") || !ft_strcmp(str, "||"))
		return (7);
	return (0);
}

int		parser(char *str, int be, int end, t_tok **t, int check)
{
	int		id;
	char	*token;

	if(!(token = ft_strsub(str, be, end - be)))
		return (0);
	id = token_analyzer(token, check);
	save_tokens(t, token, id);
	ft_memdel((void **)&token);
	return (0);
}

int		parse_token(t_tok **t, char *line)
{
	int		i;
	int		be;
	int		check;

	i = 0;
	while (line[i])
	{
		while (line[i] && ft_isblank(line[i]))
			i++;
		be = i;
		if (used_variable(line[i]))
			while (line[i] && used_variable(line[i]))
				i++;
		else
			while (line[i] && !used_variable(line[i]) && !ft_isblank(line[i]))
				i = is_inhibitors(line[i]) ? end_of_inhibitors(line, line[i], i + 1) : i + 1;
		check = used_variable(line[i]) ? 1 : 0;
		if (i > be)
			parser(line, be, i, t, check);
		else
			i++;
	}
	return (0);
}

int		analyse_tokens(t_tok *t)
{
	t_tok	*tp;

	tp = t;
	while (tp)
	{
		if (tp->id == 1 && tp->next->id != 2)
			tp->id = 0;
		if (tp->id == 2)
			tp->next->id = 3;
		tp = tp->next;
	}
	return (0);
}

t_tok	*parse_tokens(char *line)
{
	t_tok	*t;

	t = 0;
	parse_token(&t, line);
	analyse_tokens(t);
	return (t);
}
