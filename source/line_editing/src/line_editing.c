/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 04:57:19 by hastid            #+#    #+#             */
/*   Updated: 2020/02/17 15:35:48 by llachgar         ###   ########.fr       */
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

int			line_editing(char *line, int lexical)
{
	char	*l;
	char	*alias;

	l = ft_strdup(line);
	if (!tab_space(l) && !check_history_expa(&l))
	{
		if (ft_strcmp(l, line))
			ft_putendl(l);
		alias = check_alias(l);
		if (lexical)
			line_lexical(&l, &alias);
		if (!(syntax(alias)))
			execute_cmdline(alias);
		else
			ft_perror(0, 0, "syntax error !!", 1);
		do_job_notification();
		add_to_hist(ft_strdup(line), 0);
		ft_memdel((void **)&alias);
	}
	ft_memdel((void **)&l);
	return (0);
}
