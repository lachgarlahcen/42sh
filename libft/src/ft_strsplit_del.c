/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_del.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 19:03:03 by aihya             #+#    #+#             */
/*   Updated: 2019/12/27 20:14:03 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static t_node	*new_node(char *str, unsigned int start, size_t c)
{
	t_node	*node;

	if ((node = (t_node *)malloc(sizeof(t_node))) == NULL)
		return (NULL);
	if ((node->content = ft_strsub(str, start, c)) == NULL)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

static void		node_push(t_node **head, t_node *node)
{
	t_node	*curr;

	if (*head == NULL)
		*head = node;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = node;
	}
}

static char		**free_list(t_node **head)
{
	t_node	*curr;
	t_node	*next;

	if (*head)
	{
		curr = *head;
		next = curr->next;
		while (next != NULL)
		{
			ft_strdel(&(curr->content));
			free(curr);
			curr = next;
			next = curr->next;
		}
		ft_strdel(&(curr->content));
		free(curr);
	}
	return (NULL);
}

static t_node	*fill_list(char *str, char *del, size_t *counter)
{
	unsigned int	i;
	size_t			c;
	t_node			*head;
	t_node			*curr;

	head = NULL;
	curr = NULL;
	i = 0;
	while (str[i])
	{
		if (ft_strchr(del, str[i]) != NULL && ++i)
			continue ;
		else
		{
			c = 0;
			while (str[i] && ft_strchr(del, str[i]) == NULL && ++i)
				c++;
			if ((curr = new_node(str, i - c, c)) == NULL)
				return (NULL);
			node_push(&head, curr);
			(*counter)++;
		}
	}
	return (head);
}

char			**ft_strsplit_del(char *str, char *del)
{
	char	**buff;
	t_node	*head;
	t_node	*curr;
	size_t	size;
	size_t	i;

	buff = NULL;
	size = 0;
	if ((head = fill_list(str, del, &size)) == NULL)
		return (free_list(&head));
	if ((buff = (char **)malloc(sizeof(char *) * (size + 1))) == NULL)
		return (NULL);
	curr = head;
	i = 0;
	while (curr)
	{
		buff[i] = ft_strdup(curr->content);
		curr = curr->next;
		i++;
	}
	buff[i] = NULL;
	free_list(&head);
	return (buff);
}
