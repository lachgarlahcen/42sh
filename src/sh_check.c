/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 05:47:31 by hastid            #+#    #+#             */
/*   Updated: 2019/12/16 08:14:54 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

int		check_spechar(char c)
{
	if (c == '>' || c == '<' || c == '&')
		return (1);
	return (0);
}

int		check_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int		check_token(char *token)
{
	int	i;
	int	be;

	i = 0;
	while (token[i])
	{
		if (check_spechar(token[i]))
			return (1);
		if (token[i] == 34 || token[i] == 39)
		{
			be = i++;
			while (token[i] && token[i] != token[be])
				i++;
		}
		i++;
	}
	return (0);
}

int		check_number(char *token, int check)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (check && token[i] == '-' && token[i + 1] == '\0')
			return (0);
		else if (token[i] > '9' || token[i] < '0')
			return (1);
		i++;
	}
	return (0);
}

int		check_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			return (1);
		i++;
	}
	return (0);
}
