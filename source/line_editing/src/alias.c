/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 00:09:47 by hastid            #+#    #+#             */
/*   Updated: 2020/02/24 04:58:04 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

static int	check_change(char *str, int al)
{
	int	i;
	int	check;

	i = 0;
	check = 1;
	while (i < al)
	{
		if (str[i] == '&' && str[i - 1] != '>' && str[i - 1] != '<')
			check = 1;
		else if (str[i] == '|')
			check = 1;
		else if (str[i] == ';')
			check = 1;
		else if (!ft_isblank(str[i]))
			check = 0;
		i++;
	}
	return (check);
}

static int	check_is_alias(int be, int *end, char **str)
{
	char	*tp;
	char	*tmp;

	if (!(tp = ft_strsub(*str, be, *end - be)))
		return (1);
	if (!(tmp = is_alias(tp)))
		return (free_return(tp, 1));
	tmp = ft_strdup(tmp);
	*end = *end + ft_strlen(tmp);
	ft_memdel((void **)&tp);
	if ((tp = ft_strsub(*str, 0, be)))
		tmp = strjoin_free(tp, tmp, 1, 1);
	if ((tp = ft_strsub(*str, *end, ft_strlen(*str) - *end)))
		tmp = strjoin_free(tmp, tp, 1, 1);
	ft_memdel((void **)&(*str));
	*str = tmp;
	return (0);
}

char		*check_alias(char *line)
{
	int		i;
	int		be;
	char	*alias;

	i = 0;
	alias = ft_strdup(line);
	while (alias[i])
	{
		if (!ft_isblank(alias[i]) && !used_variable(alias[i]))
		{
			be = i;
			while (alias[i] && !ft_isblank(alias[i]) &&
					!used_variable(alias[i]))
				i++;
			if (check_change(alias, be))
				if (i > be)
					check_is_alias(be, &i, &alias);
		}
		else
			i++;
	}
	return (alias);
}
