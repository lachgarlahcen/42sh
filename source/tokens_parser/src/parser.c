/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 00:46:23 by hastid            #+#    #+#             */
/*   Updated: 2020/02/24 22:11:42 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_parser.h"

static int	token_analyzer(char *str, int check)
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

static int	parser(char *token, t_tok **t, int check)
{
	int		id;

	if (!token)
		return (0);
	id = token_analyzer(token, check);
	save_tokens(t, token, id);
	ft_memdel((void **)&token);
	return (0);
}

static int	parse_token(t_tok **t, char *line)
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
		if (line[i] && used_variable(line[i]))
			while (line[i] && used_variable(line[i]))
				i++;
		else
			while (line[i] && !used_variable(line[i]) && !ft_isblank(line[i]))
				i = is_inhibitors(line[i]) ?
					end_of_inhibitors(line, line[i], i + 1) : i + 1;
		check = used_variable(line[i]) ? 1 : 0;
		if (i > be)
			parser(ft_strsub(line, be, i - be), t, check);
		else
			i++;
	}
	return (0);
}

static int	analyse_tokens(t_tok *t)
{
	t_tok	*tp;

	tp = t;
	while (tp)
	{
		if (tp->id == 1 && tp->next->id != 2)
			tp->id = 0;
		if (tp->id == 2)
			tp->next->id = 3;
		if (tp->id == 2 && !ft_strcmp("<<", tp->token))
			change_tokens(tp->next);
		tp = tp->next;
	}
	return (0);
}

t_tok		*parse_tokens(char *line)
{
	t_tok	*t;

	t = 0;
	parse_token(&t, line);
	analyse_tokens(t);
	return (t);
}
