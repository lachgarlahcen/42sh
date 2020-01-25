/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 23:07:15 by hastid            #+#    #+#             */
/*   Updated: 2020/01/24 06:21:18 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"
#include <readline/readline.h>
#include <readline/history.h>

int		edit_tokens(void)
{
	t_tok	*toks;

	toks = save_environ(0)->tokens;
	while (toks)
	{
		printf("|%d| == |%s|\n", toks->id, toks->tok);
		toks = toks->next;
	}
	return (0);
}

int		check_execute(void)
{
	if (!(lexical_analyser()))
		return (edit_tokens());
	return (0);
}

int		check_blank(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
		if (!ft_isblank(line[i]) && line[i] != '\n')
			return (1);
	return (0);
}

int		main(int ac, char **av, char **env)
{
	int		ret;
	char	*line;

	ret = 0;
	(void)ac;
	(void)av;
//	signals();
//	init_history();
	init_environ();
//	init_variable(env);
	while (!ret)
	{
		if (!(line = line_editing("42sh >$ ")))
			break ;
		if (check_blank(line))
		{
			add_to_environ(line, 0);
			ret = check_execute();
			free_environ(0);
		}
		ft_memdel((void **)&line);
	}
	ft_putchar('\n');
//	free_history();
	free_environ(1);
//	free_variable();
	return (ret);
}
