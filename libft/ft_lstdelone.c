/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 17:30:23 by nsaber            #+#    #+#             */
/*   Updated: 2018/10/16 17:50:44 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = 0;
}
