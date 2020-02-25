/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 05:03:10 by aihya             #+#    #+#             */
/*   Updated: 2020/02/25 05:05:06 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		free_aliases(void)
{
	char	**names;
	int		index;

	names = aliases_names();
	index = 0;
	while (names[index])
	{
		pop_htnode(aliases(FALSE), names[index]);
		index++;
	}
	ft_chain_free(&names);
	free(aliases(FALSE));
}
