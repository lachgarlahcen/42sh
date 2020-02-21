/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:37:49 by aihya             #+#    #+#             */
/*   Updated: 2020/02/21 19:50:29 by aihya            ###   ########.fr       */
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
	hash %= HT_LIMIT;
	return (hash);
}

t_htnode	**init_hashtable(void)
{
	t_htnode	**hashtable;
	int			i;

	hashtable = (t_htnode **)malloc(sizeof(t_htnode *) * HT_LIMIT);
	if (hashtable == NULL)
		return (NULL);
	i = 0;
	while (i < HT_LIMIT)
	{
		hashtable[i] = NULL;
		i++;
	}
	return (hashtable);
}

t_htnode	*new_htnode(char *name, char *value)
{
	t_htnode	*node;

	if ((node = (t_htnode *)malloc(sizeof(t_htnode))) == NULL)
		return (NULL);
	node->name = ft_strdup(name);
	node->value = ft_strdup(value);
	node->hits = 0;
	node->next = NULL;
	return (node);
}

char		**get_names(t_htnode **hashtable, size_t size)
{
	t_htnode	*node;
	char		**names;
	int			index;
	int			ti;

	names = (char **)malloc(sizeof(char *) * (size + 1));
	if (names == NULL)
		return (NULL);
	index = 0;
	ti = 0;
	while (index < HT_LIMIT)
	{
		node = hashtable[index];
		while (node)
		{
			names[ti++] = ft_strdup(node->name);
			node = node->next;
		}
		index++;
	}
	names[ti] = NULL;
	sort(names, size);
	return (names);
}
