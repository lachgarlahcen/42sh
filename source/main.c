/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 20:14:50 by hastid            #+#    #+#             */
/*   Updated: 2020/02/05 04:12:56 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int main(int ac, char **av, char **env)
{
	int stat;
	char *line;

	(void)ac;
	(void)av;
	stat = 0;
	init_history();
	init_variables(env);
	while ((line = read_line("42sh $> ")))
	{
		line_editing(&line, 1);
		ft_memdel((void **)&line);
	}
	free_history();
	putchar('\n');
	return (stat);
}
