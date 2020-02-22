/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 22:13:14 by hastid            #+#    #+#             */
/*   Updated: 2020/02/22 22:18:09 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int		begin_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isblank(str[i]))
		i++;
	if (str[i] == ';' || str[i] == '|')
		return (1);
	if (str[i] == '&' && (!str[i + 1] ||
				(str[i + 1] != '>' && str[i + 1] != '<')))
		return (1);
	if (str[i] == '!' && !str[i + 1])
		return (1);
	return (0);
}

int		history_expa_syntax(char *str)
{
	int i;
	int	check;

	i = 0;
	check = 0;
	while (str[i])
	{
		if (str[i] == '&' || str[i] == '|' || str[i] == ';')
			check = 0;
		else if (str[i] != ' ' && str[i] != '!')
			check = 1;
		if (str[i] == '!' && !check)
		{
			while (!check && str[++i] && str[i] != '!')
				if (str[i] != ' ' && str[i] != '&' &&
						str[i] != '|' && str[i] != ';')
					check = 1;
			if (!check)
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int		check_dollar_var(char *str, int be)
{
	int	i;

	i = be;
	while (str[i] && str[i] != '}')
		i++;
	if (str[i] == '\0')
		return (1);
	if ((i - be) == 1 && (str[be] == '$' || str[be] == '?'))
		return (0);
	if (str[be] != '_' && !ft_isalnum(str[be]))
		return (1);
	while (be < i)
	{
		if (str[be] == '{' || str[be] == ' ' || str[be] == '\n')
			return (1);
		if (str[be] == '&' || str[be] == '|' || str[be] == '$')
			return (1);
		if (str[be] == '\'' || str[be] == '\"' || str[be] == '\\')
			return (1);
		be++;
	}
	return (0);
}

int		expansion_dollar(char *str)
{
	int	i;
	int	be;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			be = ++i;
			while (str[i] && str[i] != str[be])
			{
				if (str[i] == '\\' && str[be] == '\"')
					i++;
				else if (str[i] == '$' && str[i + 1] == '{' && str[be] == '\"')
					if (check_dollar_var(str, i + 2))
						return (1);
				i++;
			}
		}
		if (str[i] == '$' && str[i + 1] == '{')
			if (check_dollar_var(str, i + 2))
				return (1);
		i++;
	}
	return (0);
}
