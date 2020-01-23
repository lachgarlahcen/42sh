/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binaries.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 23:04:02 by aihya             #+#    #+#             */
/*   Updated: 2020/01/23 23:56:35 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_htnode	**binaries(int init)
{
	static t_htnode	**hashtable;

	if (init == TRUE)
		hashtable = init_hashtable();
	return (hashtable);
}

int		save_binary(char *bin_name, char *bin_value)
{
	t_htnode	*bin;

	if (bin_name == NULL || bin_value == NULL)
		return (0);
	bin = new_htnode(bin_name, bin_value);
	if (bin == NULL)
		return (0);
	push_htnode(binaries(FALSE), &bin);
	return (1);
}

char	*is_binary(char *name)
{
	t_htnode	*path;

	if ((path = find_htnode(binaries(FALSE), name)) == NULL)
		return (NULL);
	return (path->value);
}

void	remove_binary(char *name)
{
	pop_htnode(binaries(FALSE), name);
}