/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_print_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:38:15 by aihya             #+#    #+#             */
/*   Updated: 2020/02/21 20:16:07 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			print_alias(char *name, int prefix)
{
	char	*value;

	value = is_alias(name);
	if (prefix == FALSE)
		ft_printf("%s='%s'\n", name, value == NULL ? "" : value);
	else
		ft_printf("alias %s='%s'\n", name, value == NULL ? "" : value);
}

void			print_all_alias(void)
{
	char	**names;
	int		index;

	names = aliases_names(FALSE);
	index = 0;
	while (names && names[index])
	{
		print_alias(names[index], TRUE);
		index++;
	}
}
