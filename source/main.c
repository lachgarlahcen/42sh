/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 20:14:50 by hastid            #+#    #+#             */
/*   Updated: 2020/02/08 03:44:58 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	init_shell(void)
{
	if (isatty(0) && isatty(1))
		return (1);
	return (0);
}

int main(int ac, char **av, char **env)
{
	int stat;
	char *line;

	if (!init_shell())
		return (0);
	(void)ac;
	(void)av;
	stat = 0;
	signals(1);
	init_history();
	g_first_job = 0;
	init_variables(env);
	while ((line = read_line("42sh $> ")))
	{
		line_editing(&line, 1);
		ft_memdel((void **)&line);
	}
	free_variables();
	free_history();
	return (stat);
}
