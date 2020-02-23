/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 20:14:50 by hastid            #+#    #+#             */
/*   Updated: 2020/02/23 20:32:52 by aihya            ###   ########.fr       */
/*   Updated: 2020/02/22 23:51:30 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	init_shell(void)
{
	

	if (!isatty(0) || !isatty(1))
		return (1);
	g_shell_pgid = getpid();
	/*
	**Grab control of the terminal.
	*/
	g_h = 1;
	g_jobs.id = 1;
	g_jobs.f_job = 0;
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
	int	fd;
	int stat;
	char *line;
	if (init_shell())
		return (1);
	(void)ac;
	(void)av;
	fd = open("/dev/tty", O_RDWR);
	init_fd(fd);
	stat = 0;
	aliases(1);
	signals(1);
	binaries(1);
	init_history();
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
