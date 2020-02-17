/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 20:14:50 by hastid            #+#    #+#             */
/*   Updated: 2020/02/17 15:30:57 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	init_shell(void)
{
	

	if (!isatty(0) || !isatty(1))
		return (0);
	g_shell_pgid = getpid();
	/*
	**Grab control of the terminal.
	*/
	g_jobs.id = 1;
	setpgid(g_shell_pgid, g_shell_pgid);
	tcsetpgrp(STDIN_FILENO, g_shell_pgid);
	tcgetattr(STDIN_FILENO, &g_shell_tmodes);
	return (0);
}

int	exit_status(int status, int check)
{
	static int	e_status;

	if (check)
		e_status = status;
	return (e_status);
}

int	init_fd(void)
{
	int	fd;

	if ((fd = open("/dev/tty", O_RDWR) == -1))
		return (1);
	if (dup2(fd, 127) == -1)
		return (1);
	close(fd);
	if (dup2(127, 0) == -1)
		return (1);
	if (dup2(127, 1) == -1)
		return (1);
	if (dup2(127, 2) == -1)
		return (1);
	return (0);
}

int main(int ac, char **av, char **env)
{
	int stat;
	char *line;
	if (init_shell())
		return (1);
	(void)ac;
	(void)av;
	stat = 0;
	signals(1);
	init_history();
	g_jobs.f_job = 0;
	init_variables(env);
	while ((line = read_line("42sh $> ")))
	{
		line_editing(line, 1);
		ft_memdel((void **)&line);
	}
	free_variables();
	free_history();
	return (stat);
}
