/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hastid <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 17:16:59 by hastid            #+#    #+#             */
/*   Updated: 2018/10/11 19:06:48 by hastid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*l;
	t_list	*tmp;

	tmp = f(lst);
	l = tmp;
	if (lst)
	{
		while (lst->next)
		{
			lst = lst->next;
			tmp->next = f(lst);
			tmp = tmp->next;
		}
		return (l);
	}
	return (NULL);
}
