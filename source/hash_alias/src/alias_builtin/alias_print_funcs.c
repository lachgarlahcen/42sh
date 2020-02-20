/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_print_funcs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:38:15 by aihya             #+#    #+#             */
/*   Updated: 2020/02/20 01:41:13 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void			print_alias(char *name)
{
	ft_printf("alias %s='%s'\n", name, is_alias(name));
}

void			print_all_alias(void)
{
	char	**names;
	int		index;

	names = binaries_names(FALSE);
	index = 0;
	while (names[index])
	{
		print_alias(names[index]);
		index++;
	}
}
