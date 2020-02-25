/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries_add_remove.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-bouh <iel-bouh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 19:26:51 by aihya             #+#    #+#             */
/*   Updated: 2020/02/25 02:48:45 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int		save_binary(char *bin_name, char *bin_value)
{
	t_htnode	*bin;

	if (bin_name == NULL)
		return (0);
	if ((bin = find_htnode(aliases(FALSE), bin_name)) == NULL)
	{
		if ((bin = new_htnode(bin_name, bin_value)) == NULL)
			return (0);
		push_htnode(binaries(FALSE), &bin);
		binaries_counter(INC);
	}
	else
	{
		ft_strdel(&(bin->value));
		bin->value = ft_strdup(bin_value);
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
		names = binaries_names();
		index = 0;
		while (names && names[index] != NULL)
		{
			remove_binary(names[index]);
			index++;
		}
		ft_chain_free(&names);
	}
}

void	hit_binary(char *name)
{
	t_htnode	*node;

	if ((node = find_htnode(binaries(FALSE), name)))
		node->hits++;
}
