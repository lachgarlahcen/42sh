/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 04:13:44 by hastid            #+#    #+#             */
/*   Updated: 2020/02/25 03:46:42 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intern_variables.h"

int		ret_error(char *err)
{
	ft_putstr_fd("42sh : ", 2);
	ft_putstr_fd(err, 2);
	ft_putendl_fd(": not a valid variable !!", 2);
	return (1);
}

int		check_name_variables(char *name, int check)
{
	int	i;

	i = 1;
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (ret_error(name));
	while (name[i])
	{
		if (check && name[i] == '=')
			break ;
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (ret_error(name));
		i++;
	}
	return (0);
}
