/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 03:44:00 by hastid            #+#    #+#             */
/*   Updated: 2019/12/19 14:51:03 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"
#include <signal.h>

char		**list_to_tab(t_env *env)
{
	int		i;
	char	**en;
	char	*temp;
	t_env	*tmp;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	if (!i || !(en = (char **)malloc(sizeof(char *) * (i + 1))))
		return (0);
	i = 0;
	while (env)
	{
		if (!(temp = ft_strjoin(env->name, "=")))
			return (0);
		en[i++] = ft_strjoin(temp, env->value);
		ft_memdel((void **)&temp);
		env = env->next;
	}
	en[i] = 0;
	return (en);
}

int			execute_cmdl(t_tok *tok, t_env **env)
{
	int		pid;

	if ((pid = fork()) == -1)
		return (ft_perror(0, "fork failed", 1));
	if (pid == 0)
	{
		if (!duplicate(tok))
			execute_tok(tok, env);
		exit(1);
	}
	wait(0);
	return (0);
}

int			execute(t_tok *t, t_env **env)
{
	t_tok	*tp;

	tp = t;
	while (tp && tp->id != 0)
		tp = tp->next;
	if (!tp)
		return (0);
	if (check_built(tp->value))
		execute_builtins(t, env);
	else if (execute_cmdl(t, env))
		return (1);
	return (0);
}

int			cmd_line(char *line, t_env **env)
{
	t_tok	*toks;

	if (!(toks = split_tokens(line)))
		return (1);
	if (search_exit(toks))
	{
		free_tokens(toks);
		return (-1);
	}
	analy_toks(toks);
	execute(toks, env);
	free_tokens(toks);
	return (0);
}
