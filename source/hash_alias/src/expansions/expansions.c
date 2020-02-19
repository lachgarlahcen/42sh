/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 16:47:46 by aihya             #+#    #+#             */
/*   Updated: 2020/02/18 18:01:30 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

static char	*expand_exit_status(char *arg)
{
	char	*expansion;

	expansion = get_variable("?");
	ft_strojoin(&expansion, arg + 1, TRUE);
	return (expansion);
}

char		*expand(char *arg)
{
	int		index;
	char	*var;
	char	*expansion;

	if (arg[0] == '?')
		return (expand_exit_status(arg));
	var = NULL;
	index = 0;
	while (ft_isalnum(arg[index]) || arg[index] == '_')
	{
		ft_strappend(&var, arg[index], TRUE);
		index++;
	}
	expansion = get_variable(var);
	ft_strojoin(&expansion, arg + ft_strlen(var), TRUE);
	ft_strdel(&var);
	return (expansion);
}
