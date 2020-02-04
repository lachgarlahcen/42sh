/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 00:10:12 by hastid            #+#    #+#             */
/*   Updated: 2020/02/04 03:58:34 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int		is_used_variable(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<"))
		return (2);
	if (!ft_strcmp(str, ">>") || !ft_strcmp(str, "<<"))
		return (2);
	if (!ft_strcmp(str, ">&") || !ft_strcmp(str, "<&"))
		return (2);
	if (!ft_strcmp(str, "&>") || !ft_strcmp(str, "&<"))
		return (2);
	if (!ft_strcmp(str, ";") || !ft_strcmp(str, "&"))
		return (3);
	if (!ft_strcmp(str, "&&") || !ft_strcmp(str, "||") || !ft_strcmp(str, "|"))
		return (4);
	return (0);
}

int		check_value(char *str, int be, int end, int stat)
{
	int		ret;
	char	*tmp;

	if (!(tmp = ft_strsub(str, be, end - be)))
		return (0);
	if ((ret = is_used_variable(tmp)))
	{
		if (stat && (ret == 3 || ret == 4))
			return (free_return(tmp, 1));
		if (stat == 2 && ret == 2)
			return (free_return(tmp, 1));
		return (free_return(tmp, ret));
	}
	else
		return (free_return(tmp, 1));
	return (free_return(tmp, ret));
}

int		begin_syntax(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isblank(str[i]))
		i++;
	if (str[i] == ';' || str[i] == '|')
		return (1);
	if (str[i] == '&' && (!str[i + 1] || (str[i + 1] != '>' && str[i + 1] != '<')))
		return (1);
	if (str[i] == '!' && !str[i + 1])
		return (1);
	return (0);
}

int		check_syntax(int be, int end, char *str)
{
	int		i;
	int		stat;

	i = be;
	stat = 0;
	while (i < end)
	{
		be = i;
		if (used_variable(str[i]))
		{
			while (i < end && used_variable(str[i]))
				i++;
			if ((stat = check_value(str, be, i, stat)) == 1)
				return (1);
		}
		else
			i++;
	}
	return (stat);
}

int		line_syntax(char *str)
{
	int	i;
	int	be;
	int	stat;

	i = 0;
	if (begin_syntax(str))
		return (1);
	while (i >= 0 && str[i])
	{
		stat = 0;
		if (is_inhibitors(str[i]))
			i = end_of_inhibitors(str, str[i], i + 1);
		else if (used_variable(str[i]))
		{
			be = i;
			while (str[i] && (used_variable(str[i]) || str[i] == ' '))
				i++;
			if ((stat = check_syntax(be, i, str)) == 1)
				return (stat);
		}
		else
			i++;
	}
	if (i < 0)
		return ((i == -2) ? 5 : 6);
	if (stat == 2 || stat == 3)
		return ((stat == 2) ? 1 : 0);
	return (stat);
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
			i++;
			while (str[i] && str[i] != '!')
			{
				if (str[i] != ' ' && str[i] != '&' && str[i] != '|' && str[i] != ';')
					check = 1;
				if (check)
					break ;
				i++;
			}
			if (!check)
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int		expansion_dollar(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '{' && i && str[i - 1] == '$')
			count++;
		if (count > 0 && (used_variable(str[i]) ||  is_inhibitors(str[i])))
			return (1);
		if (str[i] == '}' && count > 0)
			count--;
		i++;
	}
	if (count)
		return (1);
	return (0);
}

int		syntax(char *str)
{
	if (expansion_dollar(str) || history_expa_syntax(str))
		return (1);
	return (line_syntax(str));
}
