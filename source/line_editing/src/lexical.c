/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 00:10:08 by hastid            #+#    #+#             */
/*   Updated: 2020/02/04 03:54:42 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int		line_lexical(char **str, char **alias)
{
	int		stat;
	char	*temp;

	stat = syntax(*alias);
	while (stat && stat != 1)
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
		stat = syntax(*alias);
	}
	return (0);
}
