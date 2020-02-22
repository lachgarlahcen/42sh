/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 19:07:44 by aihya             #+#    #+#             */
/*   Updated: 2020/02/22 15:21:26 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void		push_htnode(t_htnode **hashtable, t_htnode **new)
{
	t_htnode	*node;
	int			index;

	index = hash_function((*new)->name);
	node = hashtable[index];
	while (node)
	{
		if (node->next == NULL)
			break ;
		node = node->next;
	}
	if (node == NULL)
		hashtable[index] = *new;
	else
		node->next = *new;
}

void		pop_htnode(t_htnode **hashtable, char *name)
{
	t_htnode	*prev;
	t_htnode	*curr;
	int			index;

	if (name == NULL)
		return ;
	index = hash_function(name);
	prev = NULL;
	curr = hashtable[index];
	while (curr)
	{
		if (ft_strequ(name, curr->name))
		{
			if (prev == NULL)
				hashtable[index] = curr->next;
			else
				prev->next = curr->next;
			free_htnode(&curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void		free_htnode(t_htnode **a_htnode)
{
	ft_strdel(&((*a_htnode)->name));
	ft_strdel(&((*a_htnode)->value));
	free(*a_htnode);
	*a_htnode = NULL;
}

t_htnode	*find_htnode(t_htnode **hashtable, char *name)
{
	t_htnode	*node;

	node = hashtable[hash_function(name)];
	while (node != NULL)
	{
		if (ft_strequ(node->name, name))
			return (node);
		node = node->next;
	}
	return (NULL);
}
