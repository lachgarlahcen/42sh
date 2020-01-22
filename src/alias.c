/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:37:49 by aihya             #+#    #+#             */
/*   Updated: 2020/01/22 19:58:21 by aihya            ###   ########.fr       */
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

	table = (t_htnode **)malloc(sizeof(t_htnode *) * HT_LIMIT);
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

t_htnode	*new_htnode(char *name, char *value)
{
	t_htnode	*htnode;

	htnode = (t_htnode *)malloc(sizeof(t_htnode));
	if (htnode == NULL)
		return (NULL);
	htnode->name = ft_strdup(name);
	if (name != NULL && htnode->name == NULL)
		return (NULL);
	htnode->value = ft_strdup(value);
	if (name != NULL && htnode->value == NULL)
		return (NULL);
	htnode->next = NULL;
	return (htnode);
}

void		push_htnode(t_htnode **hashtable, t_htnode *htnode)
{
	t_htnode	*node;
	int			index;

	index = hash_function(htnode->name);
	node = hashtable[index];
	while (node)
	{
		if (node->next == NULL)
			break ;
		node = node->next;
	}
	if (node == NULL)
		hashtable[index] = htnode;
	else
		node->next = htnode;
}


