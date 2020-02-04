/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 02:48:48 by hastid            #+#    #+#             */
/*   Updated: 2020/02/04 03:54:58 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

static int	tab_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
	return (1);
}

void	aff_tokens(t_tok *t)
{
	while (t)
	{
		printf("%d |%s|\n", t->id, t->token);
		t = t->next;
	}
}

int	execute_cmdline(char *line)
{
	t_tok *t;

	t = parse_tokens(line);
	aff_tokens(t);
	free_toks(t);
	return (0);
}

int			line_editing(char **line, int lexical)
{
	char	*alias;

	if (!tab_space(*line) && !check_history_expa(line))
	{
		alias = check_alias(*line);
		if (lexical)
			line_lexical(line, &alias);
		if (!(syntax(alias)))
			execute_cmdline(alias);
		else
			ft_perror(0, 0, "syntax error !!", 1);
		add_history(*line);
		ft_memdel((void **)&alias);
	}
	return (0);
}
