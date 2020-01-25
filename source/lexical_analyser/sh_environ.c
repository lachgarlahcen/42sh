/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_environ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 01:46:06 by hastid            #+#    #+#             */
/*   Updated: 2020/01/24 23:55:52 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexical_analyser.h"

t_env	*save_environ(t_env **env)
{
	static t_env	*temp;

	if (env && *env)
		temp = *env;
	return (temp);
}

int		init_environ(void)
{
	t_env	*init;

	if (!(init = (t_env *)malloc(sizeof(t_env))))
		return (1);
	init->line = 0;
	init->tokens = 0;
	save_environ(&init);
	return (0);
}

void	add_to_environ(char *line, t_tok *tokens)
{
	t_env	*env;

	env = save_environ(0);
	if (line)
	{
		if (env->line)
			ft_memdel((void **)&(env->line));
		env->line = ft_strdup(line);
	}
	if (tokens)
	{
		if (env->tokens)
			free_toks(env->tokens);
		env->tokens = tokens;
	}
	save_environ(&env);
}

void	free_environ(int status)
{
	t_env	*env;

	env = save_environ(0);
	if (env->line)
	{
		ft_memdel((void **)&(env->line));
		env->line = 0;
	}
	if (env->tokens)
	{
		free_toks(env->tokens);
		env->tokens = 0;
	}
	if (status)
		ft_memdel((void **)&env);
}
