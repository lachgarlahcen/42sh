/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_checkerror.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 04:02:45 by hastid            #+#    #+#             */
/*   Updated: 2019/12/07 22:24:04 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int		check_valtok(char c)
{
	if (check_spechar(c) || c == '|')
		return (0);
	return (1);
}

static int		check_redirect(char *str)
{
	int		i;
	int		ret;
	char	*rd;

	i = 0;
	ret = 0;
	while (check_spechar(str[i]))
		i++;
	if (!(rd = ft_strsub(str, 0, i)))
		return (0);
	while (check_space(str[i]))
		i++;
	if (str[i] && check_valtok(str[i]))
	{
		if (!ft_strcmp(rd, ">") || !ft_strcmp(rd, "<"))
			ret = 1;
		if (!ft_strcmp(rd, ">>") || !ft_strcmp(rd, "<<") ||
				!ft_strcmp(rd, "<&") || !ft_strcmp(rd, "&>")
				|| !ft_strcmp(rd, "&<") || !ft_strcmp(rd, ">&"))
			ret = 2;
	}
	ft_memdel((void **)&rd);
	if (!ret)
		ft_perror(0, " syntax error near unexpected token", 1);
	return (ret);
}

static int		check_quotes(char *str, char q)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == q)
			return (i);
		i++;
	}
	return (0);
}

static int		after_pipe(char *str)
{
	int	i;

	i = 0;
	if (str[i])
	{
		while (check_space(str[i]))
			i++;
		if (str[i])
			return (0);
	}
	return (1);
}

int				check_errline(char *str)
{
	int	ret;

	while (*str)
	{
		if (*str == 34 || *str == 39)
		{
			if ((ret = check_quotes(str, *str)) == 0)
				return (2);
			str += ret + 1;
		}
		else if (check_spechar(*str))
		{
			if ((ret = check_redirect(str)) == 0)
				return (-1);
			str += ret;
		}
		else if (*str == '|')
		{
			if ((ret = after_pipe(++str)))
				return (ret);
		}
		else
			str++;
	}
	return (0);
}
