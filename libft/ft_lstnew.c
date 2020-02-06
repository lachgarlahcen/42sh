/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 13:20:52 by nsaber            #+#    #+#             */
/*   Updated: 2018/10/17 14:41:08 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *a1;

	a1 = (t_list *)malloc(sizeof(t_list));
	if (!a1)
		return (0);
	if (content)
	{
		a1->content = (void *)malloc(content_size * sizeof(void));
		if (!(a1->content))
			return (0);
		a1->content_size = content_size;
		ft_memcpy(a1->content, content, content_size);
	}
	else
	{
		a1->content = 0;
		a1->content_size = 0;
	}
	a1->next = 0;
	return (a1);
}
