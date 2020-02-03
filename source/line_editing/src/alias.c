/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 00:09:47 by hastid            #+#    #+#             */
/*   Updated: 2020/02/03 22:46:04 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

char	*is_alias(char *str)
{
	if (!ft_strcmp(str, "la"))
		return (ft_strdup("bb >> azd"));
	if (!ft_strcmp(str, "bb"))
		return (ft_strdup("ls asdasd &&"));
	return (0);
}

int		check_is_alias(int be, int end, char **str)
{
	char	*tp;
	char	*tmp;

	if (!(tp = ft_strsub(*str, be, end - be)))
		return (1);
	if (!(tmp = is_alias(tp)))
		return (free_return(tp, 1));
	ft_memdel((void **)&tp);
	if ((tp = ft_strsub(*str, 0, be)))
		tmp = strjoin_free(tp, tmp, 1, 1);
	if ((tp = ft_strsub(*str, end, ft_strlen(*str) - end)))
		tmp = strjoin_free(tmp, tp, 1, 1);
	ft_memdel((void **)&(*str));
	*str = tmp;
	return (0);
}

char	*check_alias(char *line)
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
			while (alias[i] && !ft_isblank(alias[i]) && !used_variable(alias[i]))
				i++;
			if (i > be)
				if (!check_is_alias(be, i, &alias))
					i = be;
		}
		else
			i++;
	}
	return (alias);
}
