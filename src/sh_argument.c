/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_argument.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 03:45:13 by hastid            #+#    #+#             */
/*   Updated: 2019/12/20 13:31:45 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	args_len(t_tok *toks)
{
	int	i;

	i = 0;
	while (toks)
	{
		if (toks->id == 0)
			i++;
		toks = toks->next;
	}
	return (i);
}

char		**args_execve(t_tok *t)
{
	int		i;
	char	**args;

	if (!(args = (char **)malloc(sizeof(char *) * (args_len(t) + 1))))
		return (0);
	i = 0;
	while (t)
	{
		if (t->id == 0)
		{
			if (!(args[i] = ft_strdup(t->value)))
				return (0);
			i++;
		}
		t = t->next;
	}
	args[i] = 0;
	return (args);
}

int			search_exit(t_tok *t)
{
	while (t && t->id != 0)
		t = t->next;
	if (t)
		if (!ft_strcmp("exit", t->value))
			return (1);
	return (0);
}

int			end_quotes(char *str, int be, char q)
{
	int	count;

	count = 0;
	while (str[be++])
		if (str[be] == q)
			return (be);
	return (count);
}
