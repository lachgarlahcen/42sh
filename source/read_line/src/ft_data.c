/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llachgar <llachgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/31 01:30:52 by llachgar          #+#    #+#             */
/*   Updated: 2020/02/05 03:42:49 by llachgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "read_line.h"

/*
** this add's allocate fresh memory to the new node and return a pointer to it
** if the allocation is fialed NULL is returned 
*/
t_data *new_node(char *new_data)
{
    t_data *new_node;

    if (!(new_node = (t_data *)malloc(sizeof(t_data))))
        return (NULL);
    new_node->data = new_data;
    new_node->next = NULL;
    return (new_node);
}

/*
** this function check the best postion for the new item 
** so at the end of the insertion the list will be sorted
*/

void sortedisert(t_data **head, t_data *new_node)
{
    t_data *corrent;

    if (*head == NULL || ft_strcmp((*head)->data, new_node->data) >=  0)
    {
        new_node->next = *head;
        *head = new_node;
    }
    else
    {
        corrent = *head;
        while (corrent->next != NULL && ft_strcmp((*head)->data, new_node->data) <  0)
        {
            corrent = corrent->next;
        }
        new_node->next = corrent->next;
        corrent->next = new_node;
    }
}

void free_data(t_data **head)
{
    t_data *corrent;
     t_data *to_free;

    corrent = *head;
    while (corrent)
    {
        free(corrent->data);
        to_free = corrent;
        corrent = corrent->next;
        free(to_free);
    }
}