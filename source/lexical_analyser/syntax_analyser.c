/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 00:51:19 by hastid            #+#    #+#             */
/*   Updated: 2020/01/24 23:04:12 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexical_analyser.h"

int		syntax_analyser(char *str)
{
	if (!ft_strcmp(str, "|") || !ft_strcmp(str, "&&") || !ft_strcmp(str, "||"))
		g_check(1, 1);
	else if (!ft_strcmp(str, ";") || !ft_strcmp(str, "&"))
		g_check(2, 1);
	else if (!ft_strcmp(str, ">>") || !ft_strcmp(str, "<<"))
		g_check(3, 1);
	else if (!ft_strcmp(str, ">") || !ft_strcmp(str, "<"))
		g_check(3, 1);
	else if (!ft_strcmp(str, "&>") || !ft_strcmp(str, "&<"))
		g_check(3, 1);
	else if (!ft_strcmp(str, ">&") || !ft_strcmp(str, "<&"))
		g_check(3, 1);
	else
		return (1);
	return (0);
}
