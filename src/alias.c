/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:23:31 by aihya             #+#    #+#             */
/*   Updated: 2020/01/23 23:53:40 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

t_htnode	**aliases(int init)
{
	static t_htnode	**hashtable;

	if (init == TRUE)
		hashtable = init_hashtable();
	return (hashtable);
}

int		save_alias(char *name, char *value)
{
	t_htnode	*alias;

	if (name == NULL || value == NULL)
		return (0);
	alias = new_htnode(name, value);
	if (alias == NULL)
		return (0);
	push_htnode(aliases(FALSE), &alias);
	return (1);
}

char	*is_alias(char *name)
{
	t_htnode	*alias;

	if ((alias = find_htnode(aliases(FALSE), name)) == NULL)
		return (NULL);
	return (alias->value);
}

void	unalias(char *name)
{
	pop_htnode(aliases(FALSE), name);
}

