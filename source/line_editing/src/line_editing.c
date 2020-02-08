/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 04:57:19 by hastid            #+#    #+#             */
/*   Updated: 2020/02/08 03:34:53 by hastid           ###   ########.fr       */
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

int			line_editing(char **line, int lexical)
{
	char *alias;

	if (!tab_space(*line) && !check_history_expa(line))
	{
		alias = check_alias(*line);
		if (lexical)
			line_lexical(line, &alias);
		if (!(syntax(alias)))
			execute_cmdline(alias);
		else
			ft_perror(0, 0, "syntax error !!", 1);
		add_to_hist(ft_strdup(*line), 0);
		ft_memdel((void **)&alias);
	}
	return (0);
}
