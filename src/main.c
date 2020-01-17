/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 23:07:15 by hastid            #+#    #+#             */
/*   Updated: 2019/12/23 13:28:49 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static void	kill_seg(int seg)
{
	t_cmd	*l;
	char	buf[2];

	(void)seg;
	l = NULL;
	l = keep_l(l, 1);
	if (l != NULL)
	{
		l->res = 0;
		l->ctl_c = 1;
		buf[0] = -62;
		buf[1] = 0;
		ioctl(0, TIOCSTI, buf);
	}
	else
		ft_putchar('\n');
}

char		*prompt(t_env *env)
{
	char	*tp;
	char	*ret;

	if ((tp = ft_getenv(env, "PWD")))
		tp = ft_strdup(tp);
	else
		tp = getcwd(0, 0);
	if (!tp)
		return (read_line("21sh"));
	ret = read_line(tp);
	ft_memdel((void **)&tp);
	return (ret);
}

int			main(int ac, char **av, char **env)
{
	char	*line;
	t_env	*my_env;

	(void)ac;
	(void)av;
	signal(SIGINT, kill_seg);
	signal(SIGWINCH, win_ch);
	my_env = creat_env(env);
	init_history();
	while (1337)
	{
		if (!(line = aff_prompt(my_env)))
			break ;
		if (line && *line && *line != '\n')
			if (split_lines(line, &my_env) == -1)
				break ;
		if (line)
			ft_memdel((void **)&line);
	}
	free_history();
	if (line)
		ft_memdel((void **)&line);
	free_environ(my_env);
	return (0);
}
