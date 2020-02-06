/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 10:53:13 by nsaber            #+#    #+#             */
/*   Updated: 2018/10/17 13:59:21 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;
	t_list	*temp;
	t_list	*new;

	head = 0;
	while (lst)
	{
		new = f(lst);
		new->next = 0;
		if (head == 0)
			head = new;
		else
		{
			temp = head;
			while (temp->next)
			{
				temp = temp->next;
			}
			temp->next = new;
		}
		lst = lst->next;
	}
	return (head);
}
