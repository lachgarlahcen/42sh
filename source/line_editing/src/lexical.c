/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 00:10:08 by hastid            #+#    #+#             */
/*   Updated: 2020/02/05 04:04:49 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

int line_lexical(char **str, char **alias)
{
	int stat;
	char *temp;

	stat = syntax(*alias);
	while (stat && stat != 1)
	{
		if (!(temp = read_line("$> ")))
			break;
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
