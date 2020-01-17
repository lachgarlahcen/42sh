/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 23:08:10 by hastid            #+#    #+#             */
/*   Updated: 2019/12/20 13:32:15 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static int	check_split(t_tok **toks, char *line)
{
	int		i;
	char	*temp;

	while (*line)
	{
		i = 0;
		while (line[i] && check_spechar(line[i]))
			i++;
		if (!(temp = ft_strsub(line, 0, i)) || edit_etoile(toks, temp, 1))
			return (1);
		ft_memdel((void **)&temp);
		line += i;
		if (*line)
		{
			i = -1;
			while (line[++i] && !check_spechar(line[i]))
				if (line[i] == 34 || line[i] == 39)
					i = end_quotes(line, i, line[i]);
			if (!(temp = ft_strsub(line, 0, i)) || edit_etoile(toks, temp, 1))
				return (1);
			ft_memdel((void **)&temp);
			line += i;
		}
	}
	return (0);
}

int			check_save(t_tok **toks, char *line)
{
	int		i;
	int		check;
	char	*temp;

	i = 0;
	check = 0;
	if (check_token(line))
		check = 1;
	while (line[i])
	{
		if (check && check_spechar(line[i]))
			break ;
		i++;
	}
	if (i > 0)
	{
		if (!(temp = ft_strsub(line, 0, i)))
			return (1);
		if (edit_etoile(toks, temp, check))
			return (1);
		ft_memdel((void **)&temp);
	}
	if (check)
		return (check_split(toks, line + i));
	return (0);
}

char		*sub_token(char **tmp, char *line)
{
	int	i;
	int	q;

	i = 0;
	*tmp = 0;
	while (line[i] && !check_space(line[i]))
	{
		if (line[i] == 34 || line[i] == 39)
		{
			q = i++;
			while (line[i] && line[i] != line[q])
				i++;
		}
		i++;
	}
	if (i)
		*tmp = ft_strsub(line, 0, i);
	while (line[i] && check_space(line[i]))
		i++;
	return (line + i);
}

char		*sub_line(char **tmp, char *line, char c)
{
	int	i;
	int	q;

	i = 0;
	while (line[i] && line[i] != c)
	{
		if (line[i] == 34 || line[i] == 39)
		{
			q = i++;
			while (line[i] && line[i] != line[q])
				i++;
		}
		i++;
	}
	*tmp = ft_strsub(line, 0, i);
	if (line[i])
		return (line + i + 1);
	return (line + i);
}

int			split_lines(char *line, t_env **env)
{
	char	*tmp;
	char	*temp;

	while (*line)
	{
		while (*line && check_space(*line))
			line++;
		if (*line)
		{
			line = sub_line(&tmp, line, ';');
			if (tmp && (temp = parse_line(tmp, *env)))
			{
				if (check_pipe(temp))
					split_pipe(temp, env);
				else if (cmd_line(temp, env) == -1)
				{
					ft_memdel((void **)&temp);
					return (-1);
				}
				ft_memdel((void **)&temp);
			}
		}
	}
	return (0);
}
