/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 00:10:08 by hastid            #+#    #+#             */
/*   Updated: 2020/02/03 22:47:51 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int		line_lexical(char **str, char **alias)
{
	int		stat;
	int		expa;
	char	*temp;

	stat = line_syntax(*alias);
	expa = history_expa_synatx(*alias);
	while (stat && stat != 1 && !expa)
	{
		if (!(temp = readline("$> ")))
			break ;
		if (stat == 5)
			*str = strjoin_free(*str, "\n", 1, 0);
		else if (stat != 6)
			*str = strjoin_free(*str, " ", 1, 0);
		*str = strjoin_free(*str, temp, 1, 1);
		ft_memdel((void **)&(*alias));
		*alias = check_alias(*str);
		stat = line_syntax(*alias);
		expa = history_expa_synatx(*alias);
	}
	return (0);
}
