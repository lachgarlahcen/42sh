/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 18:37:49 by aihya             #+#    #+#             */
/*   Updated: 2020/01/23 23:55:53 by aihya            ###   ########.fr       */
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

t_htnode	**init_hashtable()
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
	node->next = NULL;
	return (node);
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

void		push_htnode(t_htnode **hashtable, t_htnode **new)
{
	t_htnode	*node;
	int			index;

	index = hash_function((*new)->name);
	node = hashtable[index];
	while (node)
	{
		if (ft_strequ(node->name, (*new)->name))
		{
			ft_strdel(&(node->value));
			node->value = ft_strdup((*new)->value);
			free_htnode(new);
			return ;
		}
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

void		print_hashtable(t_htnode **hashtable)
{
	int			i;
	t_htnode	*node;

	i = 0;
	while (i < HT_LIMIT)
	{
		printf("%d:\n", i);
		node = hashtable[i];
		while (node)
		{
			printf("\t%s=%s\n", node->name, node->value);
			node = node->next;
		}
		i++;
	}
}
