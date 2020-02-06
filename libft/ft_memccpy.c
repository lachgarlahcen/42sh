/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsaber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:49:32 by nsaber            #+#    #+#             */
/*   Updated: 2018/10/12 14:02:01 by nsaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	char			*ptr;
	char			*p2;
	char			*r;

	i = 0;
	ptr = (char *)dst;
	p2 = (char *)src;
	while (i < n)
	{
		ptr[i] = p2[i];
		if ((unsigned char)ptr[i] == (unsigned char)c)
		{
			r = &ptr[++i];
			return (r);
		}
		i++;
	}
	return (0);
}
