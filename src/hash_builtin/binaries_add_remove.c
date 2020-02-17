/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries_add_remove.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 19:26:51 by aihya             #+#    #+#             */
/*   Updated: 2020/02/17 22:59:38 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		save_binary(char *bin_name, char *bin_value)
{
	t_htnode	*bin;

	if (bin_name == NULL || bin_value == NULL)
		return (0);
	bin = new_htnode(bin_name, bin_value);
	if (bin == NULL)
		return (0);
	if (push_htnode(binaries(FALSE), &bin))
	{
		binaries_counter(INC);
		binaries_names(RESET);
	}
	return (1);
}

void	remove_binary(char *name)
{
	pop_htnode(binaries(FALSE), name);
	if (binaries_counter(0) > 0)
		binaries_counter(DEC);
}

void	remove_binaries(void)
{
	char	**names;
	int		index;

	if (binaries_counter(0) > 0)
	{
		names = binaries_names(FALSE);
		index = 0;
		while (names[index] != NULL)
		{
			remove_binary(names[index]);
			index++;
		}
	}
}
