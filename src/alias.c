/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:37:49 by aihya             #+#    #+#             */
/*   Updated: 2020/01/22 19:26:08 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

int			hash_function(char *str)
{
	int	hash;
	int	i;

	hash = 0;
	i = 0;
	while (str[i])
	{
		hash += str[i];
		i++;
	}
	hash %= HASHING_LIMIT;
}

t_htnode	**init_hashtable()
{
	t_htnode	**hashtable;
	int			i;

	table = (t_htnode **)malloc(sizeof(t_htnode *) * LIMIT);
	if (table == NULL)
		return (NULL);
	i = 0;
	while (i < 100)
	{
		table[i] = NULL;
		i++;
	}
	return (table);
}


