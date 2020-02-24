/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 21:16:34 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/24 21:49:57 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	init_shell(void)
{
	int	fd;

	fd = 0;
	if (!isatty(0) || !isatty(1))
		return (1);
	g_shell_pgid = getpid();
	/*
	**Grab control of the terminal.
	*/
	g_h = 1;
	g_stat = 0;
	g_exit = 0;
	g_jobs.id = 1;
	g_jobs.f_job = 0;
	fd = open("/dev/tty", O_RDWR);
	init_fd(fd);
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

int	init_fd(int	my_fd)
{
	static int	fd;

	if (my_fd)
		fd = my_fd;
	if (!isatty(fd))
		fd = open("/dev/tty", O_RDWR);
	if (dup2(fd, 0) == -1)
		return (1);
	if (dup2(fd, 1) == -1)
		return (1);
	if (dup2(fd, 2) == -1)
		return (1);
	return (0);
}

int main(int ac, char **av, char **env)
{
	char *line;

	if (init_shell())
		return (1);
	(void)ac;
	(void)av;
	aliases(1);
	signals(1);
	binaries(1);
	init_history();
	init_variables(env);
	while (!g_exit && (line = read_line("42sh $> ")))
	{
		line_editing(line, 1);
		ft_memdel((void **)&line);
	}
	if (g_exit)
		ft_putendl("exit");
	free_jobs();
	free_variables();
	free_history();
	return (g_stat);
}
