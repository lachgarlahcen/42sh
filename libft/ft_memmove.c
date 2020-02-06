/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 21:35:20 by nsaber            #+#    #+#             */
/*   Updated: 2019/07/08 00:09:55 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	char			*p;
	char			*ps;
	char			*cp;

	cp = (char *)malloc(sizeof(char) * len);
	i = 0;
	p = (char *)dst;
	ps = (char *)src;
	while (i < len)
	{
		cp[i] = ps[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		p[i] = cp[i];
		i++;
	}
	return (p);
}
