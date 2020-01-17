/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 06:13:50 by hastid            #+#    #+#             */
/*   Updated: 2019/12/22 13:36:07 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_shell.h"

static char	*del_quotes(char *str)
{
	int		i;
	int		j;
	char	b;
	char	buf[READ_SIZE];

	i = 0;
	j = 0;
	if (!str)
		return (0);
	while (str[j] && i < READ_SIZE - 1)
	{
		if (str[j] == 34 || str[j] == 39)
		{
			b = str[j++];
			while (str[j] && str[j] != b && i < READ_SIZE - 1)
				buf[i++] = str[j++];
			j++;
		}
		else
			buf[i++] = str[j++];
	}
	buf[i] = '\0';
	ft_memdel((void **)&str);
	return (ft_strdup(buf));
}

static int	edit_tokenid(char *token, int id)
{
	if (check_token(token))
		return (4);
	if (!check_number(token, 0) && id == 1)
		return (14);
	if (id == 1)
		return (0);
	if (!check_number(token, 1) && id == 13)
		return (2);
	if (!ft_strcmp("-", token) && id == 13)
		return (3);
	if (id == 13)
		return (1);
	return (id);
}

static int	edit_redirct(char *rd)
{
	if (!ft_strcmp(rd, ">"))
		return (5);
	if (!ft_strcmp(rd, ">&"))
		return (6);
	if (!ft_strcmp(rd, ">>"))
		return (7);
	if (!ft_strcmp(rd, "<"))
		return (8);
	if (!ft_strcmp(rd, "<&"))
		return (9);
	if (!ft_strcmp(rd, "<<"))
		return (10);
	if (!ft_strcmp(rd, "&>"))
		return (11);
	if (!ft_strcmp(rd, "&<"))
		return (12);
	return (1);
}

int			analy_toks(t_tok *toks)
{
	char	*tmp;
	t_tok	*head;

	head = toks;
	while (toks)
	{
		if ((toks->id = edit_tokenid(toks->value, toks->id)) == 4)
			toks->next->id = 13;
		toks = toks->next;
	}
	toks = head;
	while (toks)
	{
		if (toks->id == 4)
			toks->id = edit_redirct(toks->value);
		if (toks->id == 10)
		{
			tmp = toks->next->value;
			if ((toks->next->value = ft_itoa(heredirect(tmp))))
				ft_memdel((void **)&tmp);
		}
		toks->value = del_quotes(toks->value);
		toks = toks->next;
	}
	return (0);
}

t_tok		*split_tokens(char *line)
{
	char	*tmp;
	t_tok	*toks;

	toks = 0;
	while (*line)
	{
		while (*line && check_space(*line))
			line++;
		if (*line)
		{
			line = sub_token(&tmp, line);
			if (tmp)
			{
				if (check_save(&toks, tmp))
				{
					ft_memdel((void **)&tmp);
					return (0);
				}
				ft_memdel((void **)&tmp);
			}
		}
	}
	return (toks);
}
