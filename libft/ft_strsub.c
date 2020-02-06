/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/13 13:33:57 by nsaber            #+#    #+#             */
/*   Updated: 2018/10/13 14:02:27 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*p;
	char			*ps;
	unsigned int	i;

	p = (char *)malloc(len + 1);
	if (!p || !s)
		return (0);
	ps = (char *)s;
	i = 0;
	while (i < len)
	{
		p[i] = ps[start];
		start++;
		i++;
	}
	p[i] = '\0';
	return (p);
}
