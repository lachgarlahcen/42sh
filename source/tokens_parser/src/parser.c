/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 00:46:23 by hastid            #+#    #+#             */
/*   Updated: 2020/02/04 02:18:30 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokens_parser.h"

int		token_analyzer(char *str)
{
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
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<"))
		return (8);
	return (0);
}

int		parser(char *str, int be, int end, t_tok **t)
{
	int		id;
	char	*token;

	if(!(token = ft_strsub(str, be, end - be)))
		return (0);
	id = token_analyzer(token);
	save_tokens(t, token, id);
	ft_memdel((void **)&token);
	return (0);
}

t_tok	*parse_tokens(char *line)
{
	int		i;
	int		be;
	t_tok	*t;

	i = 0;
	t = 0;
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
			{
				if (is_inhibitors(line[i]))
					i = end_of_inhibitors(line, line[i], i + 1);
				else
					i++;
			}
		if (i > be)
			parser(line, be, i, &t);
		else
			i++;
	}
	return (t);
}
